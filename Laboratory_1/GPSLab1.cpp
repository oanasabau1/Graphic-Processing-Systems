//
//  GPSLab1.cpp
//
//  Copyright © 2017 CGIS. All rights reserved.
//

#include "GPSLab1.hpp"



namespace gps {
    glm::vec4 TransformPoint(const glm::vec4 &point)
    {
        glm::mat4 oldTranslationMatrix(1.0f);
        glm::mat4 rotatedMatrix;
        glm::mat4 newTranslationMatrix;
        glm::vec4 newPoint;

        rotatedMatrix = glm::rotate(oldTranslationMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); ; // genereaza o matrice de rotatie cu 90.0 de grade in jurul punctului(1.0f, 0.0f, 0.0f) pe axa X
        newTranslationMatrix = glm::translate(rotatedMatrix, glm::vec3(2.0f, 0.0f, 1.0f));   // genereaza o matrice de translatie cu(2.0f, 0.0f, 1.0f)
        newPoint = newTranslationMatrix * point;  // punctul final rezultat
        return newPoint;
    }
    
    float ComputeAngle(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        //determinam modulul celor 2 vectori
        float a = glm::length(v1);  // ||a||
        float b = glm::length(v2);  // ||b||
        float c = a * b;  // ||a|| * ||b||
        float product = glm::dot(v1, v2);  //calculam produsul scalar
        product /= c;  //cosinusul celor 2 vectori
        float deg = acos(product);  //extragem valoarea unghiului 
        float finalAngle = glm::degrees(deg);  //convertire valoare
        return finalAngle;
    }
    
    bool IsConvex(const std::vector<glm::vec2>& vertices)
    {
        glm::vec3 productVector;  //vectorul rezultat in urma produsului scalar
        int i;
        int n = vertices.size();  //numarul de varfuri
        for (i = 0; i < n - 1; i++) {  //parcurgem varfurile
            glm::vec3 v1(vertices[i].x, vertices[i].y, 0.0f);
            glm::vec3 v2(vertices[i + 1].x, vertices[i + 1].y, 0.0f);
            productVector = glm::cross(v1, v2);
            if (productVector.z > 0.0f) {  //componeneta z a vectorului rezultat trebuie sa fie de acelasi semn (>0) ca poligonul sa fie CONVEX
                return false;  //altfel CONCAV
            }
        }
        //facem produsul vectorial si dintre prima si ultima muchie
        glm::vec3 v1(vertices[0].x, vertices[0].y, 0.0f);
        glm::vec3 v2(vertices[n - 1].x, vertices[n - 1].y, 0.0f);
        productVector = glm::cross(v1, v2);
        if (productVector.z > 0.0f) {
            return false;
        }
        return true;
    }
    
    std::vector<glm::vec2> ComputeNormals(const std::vector<glm::vec2>& vertices) {
        std::vector<glm::vec2> normalsList;
        glm::vec3 z(0.0f, 0.0f, 1.0f);
        int i;
        int n = vertices.size();
        if (n < 3) {
            // un poligon trebuie sa aiba minim 3 laturi
            return normalsList;
        }
        for (i = 0; i < n - 1; i++) {
            glm::vec3 v1(vertices[i].x, vertices[i].y, 0.0f);
            glm::vec3 v2(vertices[i + 1].x, vertices[i + 1].y, 0.0f);
            glm::vec3 vec = glm::cross(v2 - v1, z);
            glm::vec2 normal(vec.x, vec.y);
            glm::vec2 normalizedNormal = glm::normalize(normal);
            normalsList.push_back(normalizedNormal);
        }
        //calculam normala si dintre prima si ultima muchie
        glm::vec3 v1(vertices[n - 1].x, vertices[n - 1].y, 0.0f);
        glm::vec3 v2(vertices[0].x, vertices[0].y, 0.0f);
        glm::vec3 vec = glm::cross(v2 - v1, z);
        glm::vec2 normal(vec.x, vec.y);
        glm::vec2 normalizedNormal = glm::normalize(normal);
        normalsList.push_back(normalizedNormal);
        return normalsList;
    }
}
