#include <SDL.h>            
#include <GL/glew.h>

#include "simple_logger.h"
#include "gf3d_graphics.h"
#include "gf3d_model.h"
#include "gf3d_matrix.h"
#include "gf3d_shaders.h"

int main(int argc,char *argv[])
{
    int done = 0;
    const Uint8 * keys;
    
    GLuint program,mvp_id;
    
    Model *testmodel;
    
    Matrix4 projection,view,model,mvp;

    init_logger("gf2d.log");
    slog("gf3d begin");
    
    gf3d_graphics_initialize(
        "gametest3D",
        1200,
        700,
        1200,
        700,
        vector4d(135.0/255,196.0/255,245.0/255,1),  // background color
        0,
        3,1 // opengl major,minor 
    );

    gf3d_model_manager_init(1024);
    
    gf3d_matrix_perspective(
        projection,
        GF3D_DEGTORAD * 45,
        1200.0/700.0,
        0.1,
        100.0
    );
    
    gf3d_matrix_view(
        view,
        vector3d(4,3,3),
        vector3d(0,0,0),
        vector3d(0,1,0)
    );
    
    gf3d_matrix_identity(model);
    
    gf3d_matrix_multiply(mvp,projection,view);
    
    
//    testmodel = gf3d_model_load_from_json_file("models/cube.json");
    testmodel = gf3d_model_new_triangle();
    program = gf3d_shader_program_load("shaders/basic.vert", "shaders/basic.frag");

    // main game loop
    while(!done)
    {
        gf3d_graphics_clear_screen();
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        
        glUseProgram(program);        
        slog("using shader program %i",program);
        mvp_id = glGetUniformLocation(program, "MVP");
        glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
        gf3d_matrix_slog(mvp);
        gf3d_model_render(testmodel);
        
        gf3d_grahics_next_frame();
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    //cleanup
    gf3d_model_free(testmodel);
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/