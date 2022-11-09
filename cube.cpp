#include <math.h>
#include "cube.h"
#include "graphics.h"

/****************** Private helper methods *******************/
void Cube::reset_corners() {
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (edge_length / 2.0), center.y + (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[1] = {center.x - (edge_length / 2.0), center.y + (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[2] = {center.x + (edge_length / 2.0), center.y - (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[3] = {center.x - (edge_length / 2.0), center.y - (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[4] = {center.x + (edge_length / 2.0), center.y + (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[5] = {center.x - (edge_length / 2.0), center.y + (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[6] = {center.x + (edge_length / 2.0), center.y - (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[7] = {center.x - (edge_length / 2.0), center.y - (edge_length / 2.0), center.z - (edge_length / 2.0)};
}

void Cube::draw_point(const point &p) const {
    glVertex3f(p.x, p.y, p.z);
}

/********************** Public methods *************************/
Cube::Cube() {
    center = {0, 0, 0};
    edge_length = 50;
    reset_corners();
}

Cube::Cube(point center, unsigned int edge_length) {
    this->center = center;
    this->edge_length = edge_length;
    reset_corners();
}

void Cube::draw() const {
    glBegin(GL_QUADS);
    
    // Yellow
    glColor3f(1, 1, 0);
    draw_point(corners[0]);
    draw_point(corners[1]);
    draw_point(corners[3]);
    draw_point(corners[2]);
    
    // Magenta
    glColor3f(1, 0, 1);
    draw_point(corners[5]);
    draw_point(corners[4]);
    draw_point(corners[6]);
    draw_point(corners[7]);

    // White
    glColor3f(1, 1, 1);
    draw_point(corners[4]);
    draw_point(corners[0]);
    draw_point(corners[2]);
    draw_point(corners[6]);

    // Cyan
    glColor3f(0, 1, 1);
    draw_point(corners[1]);
    draw_point(corners[5]);
    draw_point(corners[7]);
    draw_point(corners[3]);

    // Purple
    glColor3f(0.627, 0.125, 0.941);
    draw_point(corners[4]);
    draw_point(corners[5]);
    draw_point(corners[1]);
    draw_point(corners[0]);

    // Gray
    glColor3f(0.5, 0.5, 0.5);
    draw_point(corners[7]);
    draw_point(corners[6]);
    draw_point(corners[2]);
    draw_point(corners[3]);

    glEnd();
}

void Cube::rotate(double theta_x, double theta_y, double theta_z) {
    // Initialize local variables
    double old_x = 0, old_y = 0, old_z = 0;
    double center_x = center.x, center_y = center.y, center_z = center.z;

    // Move to origin
    move(-center_x, -center_y, -center_z);

    // Rotate x
    for (point &p : corners) {
        old_y = p.y;
        old_z = p.z;
        p.y = old_y * cos(theta_x) - old_z * sin(theta_x);
        p.z = old_y * sin(theta_x) + old_z * cos(theta_x);
    }

    // Rotate y
    for (point &p : corners) {
        old_x = p.x;
        old_z = p.z;
        p.x = old_x * cos(theta_y) - old_z * sin(theta_y);
        p.z = old_x * sin(theta_y) + old_z * cos(theta_y);
    }

    // Rotate z
    for (point &p : corners) {
        old_y = p.y;
        old_x = p.x;
        p.y = old_y * cos(theta_z) - old_x * sin(theta_z);
        p.x = old_y * sin(theta_z) + old_x * cos(theta_z);
    }

    // Move back to position
    move(center_x, center_y, center_z);
}

void Cube::move(double delta_x, double delta_y, double delta_z) {
    // Moving along the x-axis
    center.x += delta_x;
    for (point &p : corners) {
        p.x += delta_x;
    }

    // Moving along the y-axis
    center.y += delta_y;
    for (point &p : corners) {
        p.y += delta_y;
    }

    // Moving along the z-axis
    center.z += delta_z;
    for (point &p : corners) {
        p.z += delta_z;
    }
}

void Cube::changeSize(double x_cof, double y_cof, double z_cof) {
    for (point &p : corners) {
        p.x *= x_cof;
        p.y *= y_cof;
        p.z *= z_cof;
    }
}