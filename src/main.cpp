#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#define WINDOW_H 720
#define WINDOW_W 1280

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

glm::vec2* VecZero(void) {
	glm::vec2* v = new glm::vec2();
	v->x = v->y = 0;
	return v;
}
class Entity {
public:
	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
	glm::vec2 vel_input;
	SDL_Color color;
	Entity(SDL_Color color_) {
		this->color = color_;
		this->pos.x = 0;
		this->pos.y = 0;
		this->vel.x = 0;
		this->vel.y = 0;
		this->acc.x = 0;
		this->acc.y = 0;
	}
private:
	bool hasGravity = false;
};

void drawEtt(Entity const* ett, SDL_FRect drawPos) {
	SDL_Color color = ett->color;
	// printf("%d %d %d %d", color.r, color.g, color.b, color.a);
	SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(g_renderer, &drawPos);
}

void physics(Entity* ett, float deltaTime, glm::vec2 const& vel_input) {
	ett->vel += deltaTime * ett->acc;
	ett->pos += deltaTime * (ett->vel + vel_input);
}

void printEtt(Entity const* ett) {
	printf("Params: pos=(%f, %f), vel=(%f, %f), acc=(%f, %f)\n", ett->pos.x, ett->pos.y, ett->vel.x, ett->vel.y, ett->acc.x, ett->acc.y);
}

int main(int argc, char const* argv[]) {
	g_window = SDL_CreateWindow("Best Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
	assert(g_window != NULL);
	g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	assert(g_renderer != NULL);

	SDL_Color red = {255, 0, 0, 255};
	Entity ett1 = Entity(red);
	printEtt(&ett1);
	ett1.acc.y += 9.81;
	ett1.pos.x += 150;
	printEtt(&ett1);

	bool run = true;
	while (run) {
		SDL_Event event;
		/* Speed modifier via inputs */
		glm::vec2 vel_modif = {0., 0.};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					run = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							run = false;
							break;
						case SDLK_LEFT:
						case SDLK_a:
							printf("left ");
							vel_modif.x -= 500;
							break;
						case SDLK_RIGHT:
						case SDLK_d:
							printf("right ");
							vel_modif.x += 500;
							break;
						case SDLK_UP:
						case SDLK_w:
							printf("up ");
							vel_modif.y -= 500;
							break;
						case SDLK_DOWN:
						case SDLK_s:
							printf("down ");
							vel_modif.y += 500;
							break;
					}
					break;
			default:
				break;
			}
		}
		SDL_Color bg_color = {89, 189, 239, 255};
		SDL_SetRenderDrawColor(g_renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
		SDL_RenderClear(g_renderer);
		physics(&ett1, 0.007, vel_modif);
		SDL_FRect rect1 = {ett1.pos.x, ett1.pos.y, 50., 50.};
		drawEtt(&ett1, rect1);
		SDL_RenderPresent(g_renderer);
	}
	std::cout << "HW ^^ uwu" << std::endl;
	return 0;
}
