#include <artComponent.h>

OverlayArtComponent::OverlayArtComponent(Entity *entity, Texture texture, int layer):
    ArtComponent(entity, layer, false),
    texture(texture.sdlTexture)
{
}