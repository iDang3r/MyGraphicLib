
#ifndef HELPFUL_FUNCTIONS_HPP
#define HELPFUL_FUNCTIONS_HPP

#define w(x) std::cout << #x << ": " << x << std::endl; 

double H(int hex) {
    return static_cast<double>(hex) / 255; 
}

void drawText(const char *text, int length, double x, double y) {
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 400, 0, 400, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(x, y);
    
    for(int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,(int)text[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

    delete [] matrix;
}

#endif // HELPFUL_FUNCTIONS_HPP