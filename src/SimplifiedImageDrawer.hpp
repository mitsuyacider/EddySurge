//
//  SimplifiedImageDrawer.hpp
//  EddySurge
//
//  Created by Mitstuya.WATANABE on 2017/04/07.
//
//

#pragma once
#ifndef SimplifiedImageDrawer_hpp
#define SimplifiedImageDrawer_hpp

#include <stdio.h>
#include "ofMain.h"
#endif /* SimplifiedImageDrawer_hpp */

class SimplifiedImageDrawer
{
public:
    
    SimplifiedImageDrawer()
    : display_list(0)
    , tex(NULL)
    {}
    
    virtual ~SimplifiedImageDrawer()
    {
        deleteDisplayList();
    }
    
    void setTexture(ofTexture& tex)
    {
        this->tex = &tex;
        tex_size.set(tex.getWidth(), tex.getHeight());
        
        deleteDisplayList();
        
        display_list = glGenLists(1);
        glNewList(display_list, GL_COMPILE);
        {
            glBegin(GL_TRIANGLE_STRIP);
            {
                glTexCoord2f(0, 0);
                glVertex2f(0, 0);
                
                glTexCoord2f(tex_size.x, 0);
                glVertex2f(1, 0);
                
                glTexCoord2f(0, tex_size.y);
                glVertex2f(0, 1);
                
                glTexCoord2f(tex_size.x, tex_size.y);
                glVertex2f(1, 1);
            }
            glEnd();
        }
        glEndList();
    }
    
    inline void draw(float x, float y, float w, float h)
    {
        assert(display_list != 0);
        
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(w, h, 1);
        glCallList(display_list);
        glPopMatrix();
    }
    
    inline void bind()
    {
        tex->bind();
    }
    
    inline void unbind()
    {
        tex->unbind();
    }
    
protected:
    
    ofTexture *tex;
    ofVec2f tex_size;
    GLint display_list;
    
    void deleteDisplayList()
    {
        if (display_list)
            glDeleteLists(display_list, 1);
        display_list = 0;
    }
};
