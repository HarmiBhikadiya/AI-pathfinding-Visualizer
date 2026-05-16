#include <GL/glut.h>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int ROWS = 20;
const int COLS = 20;
const int CELL_SIZE = 25;

int speedDelay = 30;
string algoName = "Dijkstra (Weighted)";

class Node {
public:
    int x, y;
    bool isObstacle=false, visited=false, inPath=false;
    float g=0, f=0;
    int cost=1; // random cost
    Node* parent=nullptr;

    Node(int i=0,int j=0){
        x=i; y=j;
        cost = rand()%9 + 1; // cost between 1 to 9
    }
};

struct Compare {
    bool operator()(Node* a, Node* b){ return a->f > b->f; }
};

class Grid {
public:
    vector<vector<Node>> grid;
    Node* start=nullptr;
    Node* end=nullptr;

    Grid(){
        grid.resize(ROWS, vector<Node>(COLS));
        for(int i=0;i<ROWS;i++)
            for(int j=0;j<COLS;j++)
                grid[i][j]=Node(i,j);
    }

    void reset(){
        for(auto &r:grid)
            for(auto &n:r){
                n.visited=n.inPath=false;
                n.parent=nullptr;
                n.g=n.f=0;
            }
    }

    vector<Node*> neighbors(Node* n){
        vector<Node*> res;
        //lrdu
        int dx[]={-1,1,0,0};
        int dy[]={0,0,-1,1};
        for(int k=0;k<4;k++){
            int nx=n->x+dx[k], ny=n->y+dy[k];
            if(nx>=0&&ny>=0&&nx<ROWS&&ny<COLS&&!grid[nx][ny].isObstacle)
                res.push_back(&grid[nx][ny]);
        }
        return res;
    }
};

class Pathfinder{
public:
    Grid* g;
    priority_queue<Node*,vector<Node*>,Compare> pq;//dijkstra
    queue<Node*> q; // BFS
    bool useBFS = false;
    bool running=false;

    Pathfinder(Grid* grid){g=grid;}

    void start(){
        if(!g->start||!g->end) return;
        g->reset();
        while(!pq.empty()) pq.pop();
        while(!q.empty()) q.pop();

        Node* s=g->start;
        s->g = 0;

        if(useBFS) q.push(s);
        else pq.push(s);

        running=true;
    }

    void step(){
        if(!running) return;
        Node* cur=nullptr;

        //picks the next node
        if(useBFS){
            if(q.empty()){running=false;return;}
            cur=q.front(); q.pop();
        } else {
            if(pq.empty()){running=false;return;}
            cur=pq.top(); pq.pop();
        }

        // mark it visited
        cur->visited=true;
        
        if(cur==g->end){ path(cur); running=false; return; }

        //expands neighbours and updates cost
        for(Node* nb:g->neighbors(cur)){
            if(nb->visited) continue;

            float newCost = cur->g + nb->cost;

            if(nb->parent==nullptr || newCost < nb->g){
                nb->g = newCost;
                nb->f = nb->g;
                nb->parent = cur;

                if(useBFS) q.push(nb);
                else pq.push(nb);
            }
        }
    }

    void path(Node* e){ while(e){ e->inPath=true; e=e->parent; } }
};

Grid grid;
Pathfinder pf(&grid);

void drawText(float x,float y,string text){
    glRasterPos2f(x,y);
    for(char c:text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
}

void drawCell(int i,int j){
    Node &n=grid.grid[i][j];

    if(&n==grid.start) glColor3f(0,1,0);
    else if(&n==grid.end) glColor3f(1,0,0);
    else if(n.inPath) glColor3f(1,1,0);
    else if(n.isObstacle) glColor3f(0,0,0);
    else if(n.visited) glColor3f(0,0,1);
    else glColor3f(1,1,1);

    glBegin(GL_POLYGON);
    glVertex2f(j*CELL_SIZE,i*CELL_SIZE);
    glVertex2f((j+1)*CELL_SIZE,i*CELL_SIZE);
    glVertex2f((j+1)*CELL_SIZE,(i+1)*CELL_SIZE);
    glVertex2f(j*CELL_SIZE,(i+1)*CELL_SIZE);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(j*CELL_SIZE,i*CELL_SIZE);
    glVertex2f((j+1)*CELL_SIZE,i*CELL_SIZE);
    glVertex2f((j+1)*CELL_SIZE,(i+1)*CELL_SIZE);
    glVertex2f(j*CELL_SIZE,(i+1)*CELL_SIZE);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //draw cell
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++) drawCell(i,j);
    //with colour black..
    glColor3f(0,0,0);
    //UI text
    drawText(5,ROWS*CELL_SIZE+20,"Algorithm: "+algoName);
    drawText(5,ROWS*CELL_SIZE+40,"1:Dijkstra 2:BFS | A:Run C:Clear +/- Speed");

    glFlush();
}

void timer(int){
    pf.step();
    glutPostRedisplay();
    if(pf.running) glutTimerFunc(speedDelay,timer,0);
}

void mouse(int button,int state,int x,int y){
    if(state!=GLUT_DOWN) return;
    int col=x/CELL_SIZE, row=y/CELL_SIZE;
    if(row>=ROWS||col>=COLS) return;

    if(!grid.start) grid.start=&grid.grid[row][col];
    else if(!grid.end) grid.end=&grid.grid[row][col];
    else {
        grid.grid[row][col].isObstacle=!grid.grid[row][col].isObstacle;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key,int,int){
    int mode = 0;
    if(key=='1'){ pf.useBFS=false; algoName="Dijkstra (Weighted)"; }
    if(key=='2'){ pf.useBFS=true; algoName="BFS"; }

    if(key=='a'){ pf.start(); glutTimerFunc(speedDelay,timer,0);}    
    if(key=='c'){ grid=Grid(); }
    if(key=='+'){ speedDelay=max(5,speedDelay-5); }
    if(key=='-'){ speedDelay+=5; }

    if(key == 's') mode = 1; // set start
    if(key == 'e') mode = 2; // set end
    if(key == 'o') mode = 0; // set obstacle

    glutPostRedisplay();
}

void init(){
    // initializes background colour
    glClearColor(1,1,1,1);
    // set 2D coordinate system
    //left right bottom top
    gluOrtho2D(0,COLS*CELL_SIZE,ROWS*CELL_SIZE+60,0);
}

int main(int argc,char** argv){
    srand(time(0));

    //it sets graphics system
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(COLS*CELL_SIZE,ROWS*CELL_SIZE+60);
    glutCreateWindow("Weighted Pathfinding Visualizer");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
