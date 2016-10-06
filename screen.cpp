#include "screen.h"
#include<string.h>

namespace sdlProgram{
Screen::Screen(): m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer1(NULL),m_buffer2(NULL)
{
    //Constructor
}

bool Screen::init(){  // Initialize SDL2
     if (SDL_Init(SDL_INIT_VIDEO)< 0){
        return false;
    }
 // Create an application window with the following settings:
    m_window = SDL_CreateWindow(
        "Particle Window Application",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH,                      // width, in pixels
        SCREEN_HEIGHT,                     // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (m_window == NULL) {
        // In the case that the window could not be made...
        SDL_Quit();
        return false;
    }

//    std::cout<<"success"<<std::endl;
  //function to create a 2D rendering context for a window.
   m_renderer=SDL_CreateRenderer(m_window,-1,SDL_RENDERER_PRESENTVSYNC);
   m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,                               // width, in pixels
        SCREEN_HEIGHT);

   if (m_renderer == NULL) {
        // In the case that the window could not be made...
        SDL_Quit();
        return false;
    }
    if (m_texture == NULL) {
        // In the case that the window could not be made...
        SDL_Quit();
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        return false;
    }

   m_buffer1=new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT]; //buffer f
   m_buffer2=new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

   //Sets the first number of 4 bytes of the block of memory pointed by ptr to the specified value
   memset(m_buffer1,0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
   memset(m_buffer2,0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

   return true;

}
// Generating pixel for the windows
void Screen::boxBlur(){
    Uint32 *temp=m_buffer1;
    m_buffer1=m_buffer2;
    m_buffer2=temp;

    for(int y=0;y<SCREEN_HEIGHT;y++){
            for(int x=0;x<SCREEN_WIDTH;x++){
                    int redTotal=0;
                    int greenTotal=0;
                    int blueTotal=0;

                    for(int row=-1;row<=1;row++){
                            for(int col=-1;col<=1;col++){
                                    int currentX=x+col;
                                    int currentY=y+row;
                                    if(currentX>=0 && currentX<SCREEN_WIDTH && currentY>=0 && currentY<SCREEN_HEIGHT){// setting width and height for particle window
                                            Uint32 color=m_buffer2[currentY*SCREEN_WIDTH+currentX];
                                            Uint8 red=color>>24;
                                            Uint8 green=color>>16;
                                            Uint8 blue=color>>8;

                                            redTotal+=red;
                                            greenTotal+=green;
                                            blueTotal+=blue;

                                    }
                                }
                          }
                          Uint8 red=redTotal/9;
                          Uint8 green=greenTotal/9;
                          Uint8 blue=blueTotal/9;
                          setPixel(x,y,red,green,blue);


            }

    }

}
// setting pixel window dimension and checking all the pixels stay in the dimension of window
//Uint8 is unsigned char in SDL
void Screen::setPixel(int x, int y,Uint8 red,Uint8 green,Uint8 blue){

    if(x<0 || x>=SCREEN_WIDTH || y<0 || y>=SCREEN_HEIGHT){
        return;
    }
//Left bit shift operation for generating particles values of red blue and green
    Uint32 color=0;

    color +=red;
    color<<=8; //shifting bit by 8
    color +=green;
    color<<=8;
    color +=blue;
    color<<=8;
    color +=0xFF;

    m_buffer1[(y*SCREEN_WIDTH)+x]=color;


}


//update the window with particles
void Screen::update(){
   SDL_UpdateTexture(m_texture,NULL,m_buffer1,SCREEN_WIDTH*sizeof(Uint32));
   SDL_RenderClear(m_renderer);  // Clear the entire screen to our selected color.
   SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
   SDL_RenderPresent(m_renderer); // This will show the new contents of the window.

}


bool Screen::processEvents(){
    SDL_Event event; //handle event of particle explosion here
    while(SDL_PollEvent(&event)){
            if (event.type==SDL_QUIT){
                return false;
            }
        }
    return true;
}
// close the screen and release the memory used
void Screen::close(){
   delete [] m_buffer1;
   delete [] m_buffer2;

   SDL_DestroyWindow(m_window);
   SDL_DestroyRenderer(m_renderer);
   SDL_DestroyTexture(m_texture);
   SDL_Quit();

}
}
