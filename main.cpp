#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include <sstream>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500

using namespace std;

int vp_width = 600;
int vp_height = 500;

static int win;
static int mainmenu;
static int action;
static int lineColor;
static int fillColor;
static int val =0;
static int currentActionSelected = 0; //0 means nothing selected

static GLfloat chosenColor[] = {1.0f,1.0f,1.0f};//store the line_color
static GLfloat fillChosenColor[] = {1.0f,1.0f,1.0f};//store the fill_color


std::array<int, 2> currentPt;
std::vector<std::array<int, 2>> pts;
std::vector<std::array<int, 2>> points;
bool closed = false;

//thelw domh na krataei ta polugwna,den kserw an einai swsto
//tsekare sthn 63 isws kati tetoio
std::vector<std::vector<std::array<int, 2>>> polygons;


void menu(int value)
{
    if (value ==0)
    {
        glutDestroyMenu(win);
        exit(0);
    }else{
        val = value;
    }
    glutPostRedisplay();
}

void initOpenGL() //unused for now display does all the work
{
    glClearColor(0,0,0,0);
}

void display(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if ( !pts.empty() ) //check if array is empty
    {

        glBegin(GL_LINE_STRIP);
        glColor3f(chosenColor[0],chosenColor[1],chosenColor[2]);//paint the lines
        for ( auto &pt : pts )
            glVertex2f( (float)pt[0], (float)pt[1] );
        auto &endPt = closed ? pts.front() : currentPt;
        glVertex2f( (float)endPt[0], (float)endPt[1] );

        polygons.push_back(pts);
        glEnd();

    }

    glFlush();
    glutSwapBuffers();
}

void mouse_move(int x, int y)
{
    currentPt = std::array<int, 2>{x, vp_height-y};
    glutPostRedisplay();
}

void draw_polygon(int button, int state, int x, int y)
{
    if (currentActionSelected==0)
        return;
    currentPt = std::array<int, 2>{x, vp_height-y};

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if ( closed )
            pts.clear(); // restart if last action was close
        closed = false;
        pts.push_back( currentPt );
        points.push_back(currentPt);

    }
    if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        int j =0;
        //closes polygon with the press of middle button
            for (int i=0; i<pts.size(); i++)
            {
                printf("ola ta simeia %d %d\n", points[i], points[j]);
                ++j;
            }
            points.clear()

        closed = true;
        currentActionSelected = 0;
    }
}

void actionMenu(int value)
{
    switch (value)
    {
    case 1:
        exit(0);
        break;

    case 2:
        glutDisplayFunc(display);
        glutMouseFunc(draw_polygon);
        currentActionSelected = 1; // Selected action = draw polygon
        break;
    }
}

void lineColorMenu (int value)
{
    switch (value)
    {
    case 1:

        chosenColor[0] = 1.0f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 0.0f;
        break;

    case 2:
        chosenColor[0] = 0.0f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 1.0f;
        break;

    case 3:
        chosenColor[0] = 0.0f;
        chosenColor[1] = 1.0f;
        chosenColor[2] = 0.0f;
        break;

    case 4:
        chosenColor[0] = 1.0f;
        chosenColor[1] = 1.0f;
        chosenColor[2] = 1.0f;
        break;

    case 5:
        chosenColor[0] = 0.0f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 0.0f;
        break;

    case 6:
        chosenColor[0] = 0.960784f;
        chosenColor[1] = 0.960784f;
        chosenColor[2] = 0.862745f;
        break;

    case 7:
        chosenColor[0] = 0.647059f;
        chosenColor[1] = 0.164706f;
        chosenColor[2] = 0.164706;
        break;

    case 8:
        chosenColor[0] = 1.0f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 1.0f;
        break;

    case 9:
        chosenColor[0] = 1.0f;
        chosenColor[1] = 1.0f;
        chosenColor[2] = 0.0f;
        break;

    case 10:
        chosenColor[0] = 1.0f;
        chosenColor[1] = 0.752941f;
        chosenColor[2] = 0.796078f;
        break;

    case 11:
        chosenColor[0] = 1.0f;
        chosenColor[1] = 0.843137f;
        chosenColor[2] = 0.0f;
        break;

    case 12:
        chosenColor[0] = 0.294118f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 0.509804f;
        break;

    case 13:
        chosenColor[0] = 0.12549f;
        chosenColor[1] = 0.698039f;
        chosenColor[2] = 0.666667f;
        break;

    case 14:
        chosenColor[0] = 0.0f;
        chosenColor[1] = 0.0f;
        chosenColor[2] = 0.803922f;
        break;

    case 15:
        chosenColor[0] = 0.854902f;
        chosenColor[1] = 0.439216f;
        chosenColor[2] = 0.839216f;
        break;

    case 16:
        chosenColor[0] = 0.815686f;
        chosenColor[1] = 0.12549f;
        chosenColor[2] = 0.564706f;
        break;
    }
}

void shapeColorMenu (int value)
{
   switch (value)
    {
    case 1:
        fillChosenColor[0] = 1.0f;
        fillChosenColor[1] = 0.0f;
        fillChosenColor[2] = 0.0f;
        break;

    case 2:
        exit(0);
        break;

    case 3:
        exit(0);
        break;

    case 4:
        exit(0);
        break;

    case 5:
        exit(0);
        break;

    case 6:
        exit(0);
        break;

    case 7:
        exit(0);
        break;

    case 8:
        exit(0);
        break;

    case 9:
        exit(0);
        break;

    case 10:
        exit(0);
        break;

    case 11:
        exit(0);
        break;

    case 12:
        exit(0);
        break;

    case 13:
        exit(0);
        break;

    case 14:
        exit(0);
        break;

    case 15:
        exit(0);
        break;

    case 16:
        exit(0);
        break;
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 500);
    win= glutCreateWindow("TEST");

    action = glutCreateMenu(actionMenu);
    //int sub2= glutCreateMenu(lineColorMenu);
    // int sub3= glutCreateMenu(shapeColorMenu);
    // to periergo stin glut einai oti kaneis create ta ipomenu
    //prota kai meta ta vazeis sto kentriko menu
    //ftiaxno prota ta submenu pou vriskontai mesa sto ACTION
    glutAddMenuEntry("POLYGON", 2);//create submenu2
    glutAddMenuEntry("EXIT", 1);//create submenu1

    lineColor = glutCreateMenu(lineColorMenu);

    glutAddMenuEntry("RED", 1);//RGB 1 0 0
    glutAddMenuEntry("BLUE", 2);//RGB 0 0 1
    glutAddMenuEntry("GREEN", 3);//RGB 0 1 0
    glutAddMenuEntry("WHITE", 4);//RGB 1 1 1
    glutAddMenuEntry("BLACK", 5);// RGB 0 0 0
    glutAddMenuEntry("BEIGE", 6);//RGB 0.960784 0.960784 0.862745
    glutAddMenuEntry("BROWN", 7);//RGB 0.647059 0.164706 0.164706
    glutAddMenuEntry("MAGENTA", 8);//RGB 1 0 1
    glutAddMenuEntry("YELLOW", 9);//RGB 1 1 0
    glutAddMenuEntry("PINK", 10);//RGB 1 0.752941 0.796078
    glutAddMenuEntry("GOLD", 11);//RGB 1 0.843137 0
    glutAddMenuEntry("INDIGO", 12);//RGB 0.294118 0 0.509804
    glutAddMenuEntry("LIGHTSEAGREEN", 13);//RGB 0.12549 0.698039 0.666667
    glutAddMenuEntry("MEDIUMBLUE", 14);//RGB 0 0 0.803922
    glutAddMenuEntry("ORCHID", 15);//RGB 0.854902 0.439216 0.839216
    glutAddMenuEntry("VIOLETRED", 16);//RGB 0.815686 0.12549 0.564706

    fillColor = glutCreateMenu(shapeColorMenu);

    glutAddMenuEntry("RED", 1);//RGB 1 0 0
    glutAddMenuEntry("BLUE", 2);//RGB 0 0 1
    glutAddMenuEntry("GREEN", 3);//RGB 0 1 0
    glutAddMenuEntry("WHITE", 4);//RGB 1 1 1
    glutAddMenuEntry("BLACK", 5);// RGB 0 0 0
    glutAddMenuEntry("BEIGE", 6);//RGB 0.960784 0.960784 0.862745
    glutAddMenuEntry("BROWN", 7);//RGB 0.647059 0.164706 0.164706
    glutAddMenuEntry("MAGENTA", 8);//RGB 1 0 1
    glutAddMenuEntry("YELLOW", 9);//RGB 1 1 0
    glutAddMenuEntry("PINK", 10);//RGB 1 0.752941 0.796078
    glutAddMenuEntry("GOLD", 11);//RGB 1 0.843137 0
    glutAddMenuEntry("INDIGO", 12);//RGB 0.294118 0 0.509804
    glutAddMenuEntry("LIGHTSEAGREEN", 13);//RGB 0.12549 0.698039 0.666667
    glutAddMenuEntry("MEDIUMBLUE", 14);//RGB 0 0 0.803922
    glutAddMenuEntry("ORCHID", 15);//RGB 0.854902 0.439216 0.839216
    glutAddMenuEntry("VIOLETRED", 16);//RGB 0.815686 0.12549 0.564706

    mainmenu = glutCreateMenu(menu);

    glutAddSubMenu("ACTION", action);
    glutAddSubMenu("LINE_COLOR", lineColor);
    glutAddSubMenu("FILL_COLOR", fillColor);

    //glutAddMenuEntry("RED", 1);
    //glutAddMenuEntry("GREEN", 2);
    //glutAddMenuEntry("BLUE", 3);
    //glutAddSubMenu("LINE_COLOR", sub2);
    //glutAddMenuEntry("FILL_COLOR", sub3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//right click to make menu appear

    glutDisplayFunc(display);
    glutMouseFunc(draw_polygon);

    glMatrixMode( GL_PROJECTION );
    glOrtho(0.0f, (float)vp_width, 0.0f, (float)vp_height, -1.0, 1.0);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
