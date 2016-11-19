//
// GUIslice Library Examples
// - Calvin Hass
// - http://www.impulseadventure.com/elec/microsdl-sdl-gui.html
// - Example 04: Dynamic content
//   Demonstrates push buttons, checkboxes and slider controls
//

#include "GUIslice.h"
#include "GUIslice_ex.h"

// Defines for resources
#define FONT_DROID_SANS "/usr/share/fonts/truetype/droid/DroidSans.ttf"

// Enumerations for pages, elements, fonts, images
enum {E_PG_MAIN};
enum {E_ELEM_BOX,E_ELEM_BTN_QUIT,E_ELEM_TXT_COUNT,E_ELEM_PROGRESS,
      E_ELEM_CHECK1,E_ELEM_RADIO1,E_ELEM_RADIO2,E_ELEM_SLIDER,E_ELEM_TXT_SLIDER};
enum {E_FONT_BTN,E_FONT_TXT};
enum {E_GROUP1};

bool        m_bQuit = false;

// Free-running counter for display
unsigned    m_nCount = 0;

// Instantiate the GUI
#define MAX_FONT            10
gslc_tsGui                  m_gui;
gslc_tsFont                 m_asFont[MAX_FONT];
gslc_tsXGauge               m_sXGauge;
gslc_tsXCheckbox            m_asXCheck[3];
gslc_tsXSlider              m_sXSlider;

#define MAX_PAGE            1
#define MAX_ELEM_PG_MAIN    30
gslc_tsPage                 m_asPage[MAX_PAGE];
gslc_tsElem                 m_asPageElem[MAX_ELEM_PG_MAIN];

#define MAX_STR             100

// Button callbacks
bool CbBtnQuit(void* pvGui,void *pvElem,gslc_teTouch eTouch,int nX,int nY)
{
  if (eTouch == GSLC_TOUCH_UP_IN) {
    m_bQuit = true;
  }
  return true;
}


// Create page elements
bool InitOverlays()
{
  gslc_tsElem*  pElem;
  
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPageElem,MAX_ELEM_PG_MAIN);

  
  // Background flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY_DK2);
  
  // Create background box
  pElem = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX,E_PG_MAIN,(gslc_Rect){10,50,300,150});
  gslc_ElemSetCol(pElem,GSLC_COL_WHITE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create Quit button with text label
  pElem = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN_QUIT,E_PG_MAIN,
    (gslc_Rect){160,80,80,40},"Quit",E_FONT_BTN,&CbBtnQuit);

  // Create counter
  pElem = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_Rect){20,60,50,10},
    "Count:",E_FONT_TXT);
  pElem = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_COUNT,E_PG_MAIN,(gslc_Rect){80,60,50,10},
    "",E_FONT_TXT);
  gslc_ElemSetTxtCol(pElem,GSLC_COL_YELLOW);

  // Create progress bar
  pElem = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_Rect){20,80,50,10},
    "Progress:",E_FONT_TXT);
  pElem = gslc_ElemXGaugeCreate(&m_gui,E_ELEM_PROGRESS,E_PG_MAIN,&m_sXGauge,
    (gslc_Rect){80,80,50,10},0,100,0,GSLC_COL_GREEN,false);
  
  // Create checkbox 1
  pElem = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_Rect){20,100,20,20},
    "Check1:",E_FONT_TXT);
  pElem = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK1,E_PG_MAIN,&m_asXCheck[0],
    (gslc_Rect){80,100,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_BLUE_LT2,false);

  // Create radio 1
  pElem = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_Rect){20,135,20,20},
    "Radio1:",E_FONT_TXT);
  pElem = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO1,E_PG_MAIN,&m_asXCheck[1],
    (gslc_Rect){80,135,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetGroup(pElem,E_GROUP1);

  // Create radio 2
  pElem = gslc_ElemCreateTxt(&m_gui,GSLC_ID_AUTO,E_PG_MAIN,(gslc_Rect){20,160,20,20},
    "Radio2:",E_FONT_TXT);
  pElem = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO2,E_PG_MAIN,&m_asXCheck[2],
    (gslc_Rect){80,160,20,20},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetGroup(pElem,E_GROUP1);
    
  // Create slider
  pElem = gslc_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER,E_PG_MAIN,&m_sXSlider,
    (gslc_Rect){160,140,100,20},0,100,60,5,false);
  gslc_ElemXSliderSetStyle(pElem,true,(gslc_Color){0,0,128},10,
          5,(gslc_Color){64,64,64});
  pElem = gslc_ElemCreateTxt(&m_gui,E_ELEM_TXT_SLIDER,E_PG_MAIN,(gslc_Rect){160,160,60,20},
    "Slider: ???",E_FONT_TXT);

  return true;
}


int main( int argc, char* args[] )
{
  bool                bOk = true;
  char                acTxt[100];

  // -----------------------------------
  // Initialize

  gslc_InitEnv(&m_gui);

  // Initialize the collection
  if (!gslc_Init(&m_gui,m_asPage,MAX_PAGE,m_asFont,MAX_FONT,NULL,0)) { exit(1); }
  

  gslc_InitTs(&m_gui,"/dev/input/touchscreen");

  // Load Fonts
  bOk = gslc_FontAdd(&m_gui,E_FONT_BTN,FONT_DROID_SANS,12);
  if (!bOk) { fprintf(stderr,"ERROR: FontAdd failed\n"); exit(1); }
  bOk = gslc_FontAdd(&m_gui,E_FONT_TXT,FONT_DROID_SANS,10);
  if (!bOk) { fprintf(stderr,"ERROR: FontAdd failed\n"); exit(1); }


  // -----------------------------------
  // Start display
  InitOverlays();

  // Start up display on main page
  gslc_SetPageCur(&m_gui,E_PG_MAIN);

  // Save some element references for quick access
  gslc_tsElem*  pElemCnt        = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_COUNT);
  gslc_tsElem*  pElemProgress   = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_PROGRESS);
  gslc_tsElem*  pElemSlider     = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_SLIDER);
  gslc_tsElem*  pElemSliderTxt  = gslc_PageFindElemById(&m_gui,E_PG_MAIN,E_ELEM_TXT_SLIDER);

  // -----------------------------------
  // Main event loop
  
  m_bQuit = false;
  while (!m_bQuit) {

    // General counter
    m_nCount++;

    // -----------------------------------

    // Update elements on active page
    snprintf(acTxt,MAX_STR,"%u",m_nCount);
    gslc_ElemSetTxtStr(pElemCnt,acTxt);

    gslc_ElemXGaugeUpdate(pElemProgress,((m_nCount/200)%100));
    
    // TODO: Replace with Slider callback
    int nPos = gslc_ElemXSliderGetPos(pElemSlider);  
    snprintf(acTxt,MAX_STR,"Slider: %u",nPos);
    gslc_ElemSetTxtStr(pElemSliderTxt,acTxt);
    
    // Periodically call GUIslice update function    
    gslc_Update(&m_gui);

  } // bQuit

  // Read checkbox state
  // - Either read individual checkboxes
  //   bool bCheck = gslc_ElemXCheckboxGetState(&m_gui,E_ELEM_CHECK1);
  // - Or find one in the group that was checked (eg. for radio buttons)
  //   gslc_tsElem* pElem = gslc_ElemXCheckboxFindChecked(&m_gui,GSLC_GROUP_ID_NONE);

  // -----------------------------------
  // Close down display

  gslc_Quit(&m_gui);

  return 0;
}
