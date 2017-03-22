#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*background2,*character,*character2,*character4,*character6,*character7,*fondo3,*fondo4, *my_image;
SDL_Rect rect_background,rect_background2,rect_character,rect_character2,rect_character4,rect_character6,rect_character7,fondo3_rect,fondo4_rect, my_rect;

vector<SDL_Texture*> personaje_texture;
SDL_Rect rect_personaje;
int current_personaje = 0;

bool estaColisionando(SDL_Rect a, SDL_Rect b)
{
    a= rect_personaje;
    b= rect_character4;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}
bool c3(SDL_Rect a, SDL_Rect b)
{
    a= rect_personaje;
    b= rect_character7;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}
bool c2(SDL_Rect a, SDL_Rect b)
{
    a= rect_personaje;
    b= rect_character2;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}
//Main Loop

    void pantalla2()
{
    //Guardar archivo
    ofstream archivo("archivo.txt");
    archivo<<"Mision cumplida"<<endl;
    archivo.close();
    //Generar segunda pantalla
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
               break;
            }
        }

        SDL_RenderCopy(renderer, fondo3, NULL, &fondo3_rect);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
}
int main( int argc, char* args[] )
{
    int i=0;
//Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
//Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
//SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }
//Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;
    background2 = IMG_LoadTexture(renderer,"fondo2.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background2.x = 1200;
    rect_background2.y = 0;
    rect_background2.w = 1200;
    rect_background2.h = 600;
     fondo3 = IMG_LoadTexture(renderer,"vic.jpg");
    SDL_QueryTexture(background2, NULL, NULL, &w, &h);
    fondo3_rect.x = 0;
    fondo3_rect.y = 0;
    fondo3_rect.w = 1200;
    fondo3_rect.h = 600;

    character2 = IMG_LoadTexture(renderer, "b1.png");
    SDL_QueryTexture(character2, NULL, NULL, &w, &h);
    rect_character2.x = 250;
    rect_character2.y = 0;
    rect_character2.w = 50;
    rect_character2.h = 25;
    character = IMG_LoadTexture(renderer, "suelo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 500;
    rect_character.w = 1200;
    rect_character.h = 200;
    character4 = IMG_LoadTexture(renderer, "b2.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character4.x = 1000;
    rect_character4.y = 500;
    rect_character4.w = 50;
    rect_character4.h = 25;
    character6 = IMG_LoadTexture(renderer, "logo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character6.x = 1000;
    rect_character6.y = 500;
    rect_character6.w = 100;
    rect_character6.h = 50;
    character7 = IMG_LoadTexture(renderer, "snake.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character7.x = 1000;
    rect_character7.y = 500  ;
    rect_character7.w = 150;
    rect_character7.h = 150;
    personaje_texture.push_back(IMG_LoadTexture(renderer, "p1.png"));
    personaje_texture.push_back(IMG_LoadTexture(renderer, "p2.png"));
    rect_personaje.x = 0;
    rect_personaje.y = 300;



    my_image = IMG_LoadTexture(renderer, "image.png");
    my_rect.x = 1200;
    my_rect.y = 600;
    my_rect.w = 50;
    my_rect.h = 50;
    int velocidad = 5;
     int frames = 0;
//Main Loop
    char orien= 'u';
    char tation= 'a';
    char snake= 'r';
    bool game_over = false;
    int gravedad = 1;
    int piso = 300;
    int velocidad_y = 5;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            i++;
//mover background
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_background.x-=5;
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_background2.x-=5;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_background.x+=5;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_background2.x+=5;
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
// p1,p2
        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            rect_personaje.x-=velocidad;
        }
        if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
            rect_personaje.x+=velocidad;
        }
//mover y regresar b1
        if(rect_character2.x>1200)
        {
            orien='u';
        }
        if(rect_character2.x<0)
        {
            orien='d';
        }
        if(orien =='d')
        {
            rect_character2.x+=1;
        }
        if(orien == 'u')
        {
            rect_character2.x-=1;
        }
        //snake
        if(rect_character7.x>1200)
        {
            snake='l';
        }
        if(rect_character7.x<0)
        {
            snake='r';
        }
        if(snake =='r')
        {
            rect_character7.x+=1;
        }
        if(snake == 'l')
        {
            rect_character7.x-=1;
        }
//mover y regresar b2
        if(rect_character4.y>600)
        {
            tation='b';
        }
        if(rect_character4.y<0)
        {
            tation='a';
        }
        if(tation =='a')
        {
            rect_character4.y+=1;
        }
        if(tation == 'b')
        {
            rect_character4.y-=1;
        }
        velocidad_y+=gravedad;
        rect_personaje.y += velocidad_y;
        if(rect_personaje.y>piso)
            rect_personaje.y = piso;
//colision
        if(estaColisionando(rect_character,my_rect))
        {
            return game_over;
        }
        if(c2(rect_character,my_rect))
        {
            return game_over;
        }
        if(c3(rect_character,my_rect))
        {
            return game_over;
        }

     if(frames%10==0)
        {
            current_personaje++;
            if(current_personaje >= personaje_texture.size())
            {
                current_personaje = 0;
            }
        }
         if(rect_personaje.x>1200)
        {
            pantalla2();
        }
        if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
        {
            if(rect_personaje.y == piso)
                velocidad_y = -40  ;
        }
        if(Event.key.keysym.sym == SDLK_ESCAPE)
        {
            return game_over;
        }
        frames++;
    SDL_QueryTexture(personaje_texture[0], NULL, NULL, &rect_personaje.w, &rect_personaje.h);
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, background2, NULL, &rect_background2);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderCopy(renderer, character2, NULL, &rect_character2);
        SDL_RenderCopy(renderer, character4, NULL, &rect_character4);
        SDL_RenderCopy(renderer, character6, NULL, &rect_character6);
        SDL_RenderCopy(renderer, character7, NULL, &rect_character7);
        SDL_RenderCopy(renderer, my_image, NULL, &my_rect);
         SDL_RenderCopy(renderer, personaje_texture[current_personaje], NULL, &rect_personaje);
        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }
    return 0;
}
