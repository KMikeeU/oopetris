#include "renderer.hpp"

static constexpr SDL_Rect to_sdl_rect(Rect rect) {
    return SDL_Rect{ rect.top_left.x, rect.top_left.y, rect.bottom_right.x - rect.top_left.x + 1,
                     rect.bottom_right.y - rect.top_left.y + 1 };
}

Renderer::Renderer(Window& window) {
    m_renderer = SDL_CreateRenderer(window.get_sdl_window(), -1, 0);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
}

void Renderer::set_draw_color(Color color) const {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

void Renderer::clear(Color clear_color) const {
    set_draw_color(clear_color);
    SDL_RenderClear(m_renderer);
}

void Renderer::draw_rect_filled(Rect rect, Color color) const {
    set_draw_color(color);
    SDL_Rect sdl_rect = to_sdl_rect(rect);
    SDL_RenderFillRect(m_renderer, &sdl_rect);
}

void Renderer::draw_rect_outline(Rect rect, Color color) const {
    set_draw_color(color);
    SDL_Rect sdl_rect = to_sdl_rect(rect);
    SDL_RenderDrawRect(m_renderer, &sdl_rect);
}

void Renderer::present() const {
    SDL_RenderPresent(m_renderer);
}

void Renderer::draw_line(Point from, Point to, Color color) const {
    set_draw_color(color);
    SDL_RenderDrawLine(m_renderer, from.x, from.y, to.x, to.y);
}
