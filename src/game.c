#include <SDL.h>            

#include "simple_logger.h"
#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_matrix.h"
#include "gf3d_camera.h"
#include "gf3d_vector.h"
#include "gf3d_texture.h"

int main(int argc,char *argv[])
{
    int done = 0;
	double camera_bound = 0;
    const Uint8 * keys;
	const Uint8 * mouse;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    Model *model;
    Model *model2;
    Model *model3;
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        1                       //validation
    );
    
    // main game loop
    slog("gf3d main loop begin");
    model = gf3d_model_load("agumon");
    model2 = gf3d_model_load("EGX");
    model3 = gf3d_model_load("cube");
	//gf3d_vgraphics_rotate_camera_X(0);

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		mouse = SDL_GetMouseState(NULL, NULL);

        //update game things here
        
		//gf3d_vgraphics_rotate_camera_Z(0.001);
		//gf3d_vgraphics_rotate_camera_Z(0.001);
        
        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
        commandBuffer = gf3d_command_rendering_begin(bufferFrame);

			//gf3d_model_draw(model,bufferFrame,commandBuffer);
            gf3d_model_draw(model2,bufferFrame,commandBuffer);
            
        gf3d_command_rendering_end(commandBuffer);
        gf3d_vgraphics_render_end(bufferFrame);

		
		if (keys[SDL_SCANCODE_Q])gf3d_vgraphics_rotate_camera_X(0.02);
		if (keys[SDL_SCANCODE_E])gf3d_vgraphics_rotate_camera_X(-1 * 0.02);

		if (keys[SDL_SCANCODE_S])gf3d_vgraphics_rotate_camera_Y(0.02);
		if (keys[SDL_SCANCODE_W])gf3d_vgraphics_rotate_camera_Y(-1 * 0.02);

		if (keys[SDL_SCANCODE_D])gf3d_vgraphics_rotate_camera_Z(0.02);
		if (keys[SDL_SCANCODE_A])gf3d_vgraphics_rotate_camera_Z(-1 * 0.02);
		

		if (keys[SDL_SCANCODE_LCTRL] && (camera_bound > -15.0)) {
			camera_bound -= 0.1;
			slog("%lf", camera_bound);
			gf3d_vgraphics_zoom(camera_bound);
		}

		if(keys[SDL_SCANCODE_LALT] && (camera_bound < 15.0)) {
			camera_bound += 0.1;
			slog("%lf", camera_bound);
			gf3d_vgraphics_zoom(camera_bound);
		}

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
