//
//  main.cpp
//  Assi
//
//  Created by Isra Ragheb on 11/14/18.
//  Copyright © 2018 DBB. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <math.h>

using namespace std;

//Quetion 1(Implemntation)
void marchingSquares(int rows,int coloums,int** file){
    int contour[rows][coloums];
    string st1,st2,st3,st4;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<coloums; j++) {
            contour[i][j]=0;
        }
    }
    cout<< '\n';
    
    for (int i=0; i<rows; i++) {
        for (int j=0; j<coloums; j++) {
            string cmpstr;
            
            int plusi=i+1;
            int plusj=j+1;
            int fi,fj;
            if(plusi<rows){
                fi=plusi;
            }
            else{
                fi=i;
            }
            if(plusj<coloums){
                fj=plusj;
            }
            else{
                fj=j;
            }
            std::stringstream str;
            str << file[i][j];
            str << file[i][fj];
            str << file[fi][j];
            str << file[fi][fj];
            cmpstr=str.str();
            
            //right
            if(cmpstr=="0100"|| cmpstr=="0000" || cmpstr=="1100" || cmpstr=="1110"){
                if(file[fi][j]==1 && file[i][j]==1 ){
                    contour[fi][j]=file[fi][j];
                    contour[i][j]=0;
                }
                else{
                    contour[i][j]=file[i][j];
                    contour[fi][j]=file[fi][j];
                }
                
            }
            else{
                //left
                if(cmpstr=="0011" || cmpstr=="0111" ||cmpstr=="0110" ||cmpstr=="0010"){
                    if( file[fi][j]==1 && file[i][j]==1){
                        contour[fi][j]=file[fi][j];
                    }
                    else{

                        contour[i][j]=file[i][j];
                        contour[fi][j]=file[fi][j];
                    }
                    
                }
                else{
                    //up
                    if(cmpstr=="1000" || cmpstr=="1011" || cmpstr=="1001" ||cmpstr=="1010"){
                        if( file[fi][j]==1&& file[i][j]==1){
                            contour[fi][j]=file[fi][j];
                        }
                        else{
                            contour[i][j]=file[i][j];
                            contour[fi][j]=file[fi][j];
                        }                    }
                    else{
                        //down
                        if(cmpstr=="0101" || cmpstr=="0001" || cmpstr=="1101"){
                            if(file[fi][j]==1&& file[i][j]==1){
                                contour[fi][j]=file[fi][j];
                            }
                            else{
                                contour[i][j]=file[i][j];
                                contour[fi][j]=file[fi][j];
                            }
                        }
                    }
                    
                }
                
            }
        }
    }
    
        for (int i=0; i<rows; i++) {
                for (int j=0;j<coloums; j++) {
                    cout << contour[i][j];
                }
                cout<< '\n';
            }
}

//Used to get the rows and coloums of the text file
std::pair<int , int> getsize(string filepath){
    string line;
    ifstream myfile (filepath);
    int colums=0;
    int rows=0;
    int count=0;
    if( myfile.is_open()){
        while (getline(myfile,line)){
             count = 0;
            //Checking for white spaces inside the string
            for (int i = 0; i < line.length(); i++)
            {
                if (isspace(line.at(i)))
                {
                    count++;
                }
            }
            rows++;
        }
        colums=count+1;
        myfile.close();
    }
    else {
        cout << "Unable to open file";
    }
    
    return std::make_pair(colums, rows);
}

//Used to open files
int** openfile(string filepath,int rows,int coloums){
    char myfile[filepath.length()+1];
    FILE * pFile;
    int file [rows][coloums];
    strcpy(myfile, filepath.c_str());
    pFile = fopen(myfile,"r");
    int **result=new int*[rows];

    for (int i=0; i<rows; i++) {
        for(int j=0;j<coloums;j++){
            int n;
            fscanf(pFile, "%d", &n);
            file[i][j]=n;
        }
    }
            for (int i=0; i<rows; i++) {
                result[i]=new int[coloums];
                for (int j=0;j<coloums; j++) {
                    result[i][j]=file[i][j];
                }
                cout<< '\n';
            }
    return result;
}

//Question 2 (intailization of the drawing window)
void init(void) {
    glClearColor(255, 255, 255, 255);
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Question 2(Part 1 drawing the stickman at the orgin)
void drawstickman(int one ,int two, int three,int four, int five){
    //line1
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(0, 0,0);
    glVertex3f(0, five,0);
    glEnd();
    glPopMatrix();
   
    //line2
    glPushMatrix();
    glTranslated(0,five,0);
    glRotated(45, 0,0,1);
    glTranslated(0,-five,0);
    glBegin(GL_LINES);
    glVertex3f(0, five,0);
    glVertex3f(0, five+one,0);
    glEnd();
    glPopMatrix();

    
    //line3
    glPushMatrix();
    glTranslated(0,five,0);
    glRotated(-45, 0,0, 1);
    glTranslated(0,-five,0);
    glBegin(GL_LINES);
    glVertex3f(0, five,0);
    glVertex3f(0, five+two,0);
    glEnd();
    glPopMatrix();
    
    
    //line4
    glPushMatrix();
    glRotated(45, 0,0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0,0);
    glVertex3f(0,-three,0);
    glEnd();
    glPopMatrix();
    
    //line5
    glPushMatrix();
    glRotated(-45, 0,0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0,0);
    glVertex3f(0,-four,0);
    glEnd();
    glPopMatrix();
    glFlush();
    
}

//Question 2(Part 1 translating the stickmans)
void drawLines(int** file) {
    int count=0;
    int x=10;
    int y=480;
    for (int i=0; i<100; i++) {
        for (int j=0; j<100; j++){
            glPushMatrix();
            glTranslated(x,y,0);
            drawstickman(file[count][4]*0.02,file[count][0]*0.02,file[count][1]*0.02, file[count][2]*0.02, file[count][3]*0.02);
            glPopMatrix();
            x=x+5;
            count++;
        }
        x=0;
        y=y-10;
    }
    glFlush();
}


//Question 2(Part 2)
void shapeCoding(int** file){
    int accesscount=0;
    int countrow=0;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0);
    for(int i=0;i<500;i++){
        for(int j=0;j<20;j++){
            int shapecl1=file[accesscount][0];
            int shapecl2=file[accesscount][1];
            int shapecl3=file[accesscount][2];
            int shapecl4=file[accesscount][3];
            int shapecl5=file[accesscount][4];
            
            
            glColor3b(shapecl1, shapecl1,shapecl1);
            
            glPushMatrix();
            glBegin(GL_POINTS);
            glVertex2d(j+countrow, i);
            glEnd();
            
            glColor3b(shapecl2, shapecl2,shapecl2);
            
            glBegin(GL_POINTS);
            glVertex2d(j+countrow+1, i);
            glEnd();
            
            glColor3b(shapecl3, shapecl3,shapecl3);
            glBegin(GL_POINTS);
            glVertex2d(j+countrow+2, i);
            glEnd();
            
            glColor3b(shapecl4, shapecl4,shapecl4);
            glBegin(GL_POINTS);
            glVertex2d(j+countrow+3, i);
            glEnd();
            
            glColor3b(shapecl5, shapecl5,shapecl5);
            glBegin(GL_POINTS);
            glVertex2d(j+countrow+4, i);
            glEnd();
            glPopMatrix();
            
            accesscount++;
            
            countrow+=4;
        }
        countrow=0;
    }
    glFlush();
}

//Question 2(Part 3)
void SpiralTecheniquie(){
    
}

void display(){
    glPushMatrix();
    int coloums ,rows;
    std::tie(coloums,rows)=getsize("/Users/israragheb/Desktop/A2/Points.txt");
    //drawLines(openfile("/Users/israragheb/Desktop/A2/Points.txt", rows, coloums));
    shapeCoding(openfile("/Users/israragheb/Desktop/A2/Points.txt", rows, coloums));
    glPopMatrix();
    
}


int main(int argc, char** argv) {

    //Question 1
//    int coloums ,rows;
//    std::tie(coloums,rows)=getsize("/Users/israragheb/Desktop/A2/BinaryImage.txt");
//    marchingSquares(rows, coloums, openfile("/Users/israragheb/Desktop/A2/BinaryImage.txt",rows,coloums));

    
    //Question 2
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(1000,1000);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutCreateWindow("Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
