/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/
/*
    MaSzyna EU07 locomotive simulator
    Copyright (C) 2001-2004  Marcin Wozniak and others

*/

#pragma once

#include "Classes.h"
#include "dumb3d.h"
#include "Float3d.h"
#include "Model3d.h"
#include "DynObj.h"
#include "scenenode.h"

const int iMaxNumLights = 8;
float const DefaultDarkThresholdLevel { 0.325f };

// typy stanu świateł
enum TLightState {
    ls_Off = 0, // zgaszone
    ls_On = 1, // zapalone
    ls_Blink = 2, // migające
    ls_Dark = 3, // Ra: zapalajce się automatycznie, gdy zrobi się ciemno
    ls_Home = 4 // like ls_dark but off late at night
};

class TAnimVocaloidFrame
{ // ramka animacji typu Vocaloid Motion Data z programu MikuMikuDance
  public:
    char cBone[15]; // nazwa kości, może być po japońsku
    int iFrame; // numer ramki
    float3 f3Vector; // przemieszczenie
    float4 qAngle; // kwaternion obrotu
    char cBezier[64]; // krzywe Béziera do interpolacji dla x,y,z i obrotu
};

class basic_event;

class TAnimContainer
{ // opakowanie submodelu, określające animację egzemplarza - obsługiwane jako lista
    friend TAnimModel;

  private:
    Math3D::vector3 vRotateAngles; // dla obrotów Eulera
    Math3D::vector3 vDesiredAngles;
    double fRotateSpeed;
    Math3D::vector3 vTranslation;
    Math3D::vector3 vTranslateTo;
    double fTranslateSpeed; // może tu dać wektor?
    float4 qCurrent; // aktualny interpolowany
    float4 qStart; // pozycja początkowa (0 dla interpolacji)
    float4 qDesired; // pozycja końcowa (1 dla interpolacji)
    float fAngleCurrent; // parametr interpolacyjny: 0=start, 1=docelowy
    float fAngleSpeed; // zmiana parametru interpolacji w sekundach
    TSubModel *pSubModel;
    float4x4 *mAnim; // macierz do animacji kwaternionowych
    // dla kinematyki odwróconej używane są kwaterniony
    float fLength; // długość kości dla IK
    int iAnim; // animacja: +1-obrót Eulera, +2-przesuw, +4-obrót kwaternionem, +8-IK
    //+0x80000000: animacja z eventem, wykonywana poza wyświetlaniem
    //+0x100: pierwszy stopień IK - obrócić w stronę pierwszego potomnego (dziecka)
    //+0x200: drugi stopień IK - dostosować do pozycji potomnego potomnego (wnuka)
    union
    { // mogą być animacje klatkowe różnego typu, wskaźniki używa AnimModel
        TAnimVocaloidFrame *pMovementData; // wskaźnik do klatki
    };
    basic_event *evDone; // ewent wykonywany po zakończeniu animacji, np. zapór, obrotnicy
  public:
    TAnimContainer *pNext;
    TAnimContainer *acAnimNext; // lista animacji z eventem, które muszą być przeliczane również bez
    // wyświetlania
    TAnimContainer();
    ~TAnimContainer();
    bool Init(TSubModel *pNewSubModel);
    inline
    std::string NameGet() {
        return (pSubModel ? pSubModel->pName : ""); };
    void SetRotateAnim( Math3D::vector3 vNewRotateAngles, double fNewRotateSpeed);
    void SetTranslateAnim( Math3D::vector3 vNewTranslate, double fNewSpeed);
    void AnimSetVMD(double fNewSpeed);
    void PrepareModel();
    void UpdateModel();
    void UpdateModelIK();
    bool InMovement(); // czy w trakcie animacji?
    inline
    double AngleGet() {
        return vRotateAngles.z; }; // jednak ostatnia, T3D ma inny układ
    inline
    Math3D::vector3 TransGet() {
        return Math3D::vector3(-vTranslation.x, vTranslation.z, vTranslation.y); }; // zmiana, bo T3D ma inny układ
    inline
    void WillBeAnimated() {
        if (pSubModel)
            pSubModel->WillBeAnimated(); };
    void EventAssign(basic_event *ev);
    inline
    basic_event * Event() {
        return evDone; };
};

class TAnimAdvanced
{ // obiekt zaawansowanej animacji submodelu
  public:
    TAnimVocaloidFrame *pMovementData;
    unsigned char *pVocaloidMotionData; // plik animacyjny dla egzemplarza (z eventu)
    double fFrequency; // przeliczenie czasu rzeczywistego na klatki animacji
    double fCurrent; // klatka animacji wyświetlona w poprzedniej klatce renderingu
    double fLast; // klatka kończąca animację
    int iMovements;
    TAnimAdvanced();
    ~TAnimAdvanced();
    int SortByBone();
};

// opakowanie modelu, określające stan egzemplarza
class TAnimModel : public scene::basic_node {

    friend opengl_renderer;
    friend opengl33_renderer;
    friend itemproperties_panel;

public:
// constructors
    explicit TAnimModel( scene::node_data const &Nodedata );
// destructor
    ~TAnimModel();
// methods
    static void AnimUpdate( double dt );
    bool Init(std::string const &asName, std::string const &asReplacableTexture);
    bool Load(cParser *parser, bool ter = false);
    TAnimContainer * AddContainer(std::string const &Name);
    TAnimContainer * GetContainer(std::string const &Name = "");
    void LightSet( int const n, float const v );
    void SkinSet( int const Index, material_handle const Material );
    void AnimationVND( void *pData, double a, double b, double c, double d );
    int TerrainCount();
    TSubModel * TerrainSquare(int n);
    int Flags();
    inline
    material_data const *
        Material() const {
            return &m_materialdata; }
    inline
    TModel3d *
        Model() const {
            return pModel; }
    inline
    void
        Angles( glm::vec3 const &Angles ) {
            vAngle = Angles; }
    inline
    glm::vec3
        Angles() const {
            return vAngle; }
// members
    static TAnimContainer *acAnimList; // lista animacji z eventem, które muszą być przeliczane również bez wyświetlania

private:
// methods
    void RaPrepare(); // ustawienie animacji egzemplarza na wzorcu
    void RaAnimate( unsigned int const Framestamp ); // przeliczenie animacji egzemplarza
    void Advanced();
    // radius() subclass details, calculates node's bounding radius
    float radius_();
    // serialize() subclass details, sends content of the subclass to provided stream
    void serialize_( std::ostream &Output ) const;
    // deserialize() subclass details, restores content of the subclass from provided stream
    void deserialize_( std::istream &Input );
    // export() subclass details, sends basic content of the class in legacy (text) format to provided stream
    void export_as_text_( std::ostream &Output ) const;
    // checks whether provided token is a legacy (text) format keyword
    bool is_keyword( std::string const &Token ) const;

// members
    TAnimContainer *pRoot { nullptr }; // pojemniki sterujące, tylko dla aniomowanych submodeli
    TModel3d *pModel { nullptr };
    glm::vec3 vAngle; // bazowe obroty egzemplarza względem osi
    material_data m_materialdata;

    std::string asText; // tekst dla wyświetlacza znakowego
    TAnimAdvanced *pAdvanced { nullptr };
    // TODO: wrap into a light state struct, remove fixed element count
    int iNumLights { 0 };
    std::array<TSubModel *, iMaxNumLights> LightsOn {}; // Ra: te wskaźniki powinny być w ramach TModel3d
    std::array<TSubModel *, iMaxNumLights> LightsOff {};
    std::array<float, iMaxNumLights> lsLights {}; // ls_Off
    std::array<glm::vec3, iMaxNumLights> m_lightcolors; // -1 in constructor
    std::array<float, iMaxNumLights> m_lighttimers {};
    std::array<float, iMaxNumLights> m_lightopacities; // {1} in constructor
    float fOnTime { 1.f / 2 };// { 60.f / 45.f / 2 };
    float fOffTime { 1.f / 2 };// { 60.f / 45.f / 2 }; // były stałymi, teraz mogą być zmienne dla każdego egzemplarza
//    float fTransitionTime { fOnTime * 0.9f }; // time
    bool m_transition { true }; // smooth transition between light states
    unsigned int m_framestamp { 0 }; // id of last rendered gfx frame
};



class instance_table : public basic_table<TAnimModel> {

};

//---------------------------------------------------------------------------
