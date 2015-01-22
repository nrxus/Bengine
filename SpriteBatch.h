#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace Bengine{
  enum class GlyphSortType {
    NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE
			};

  class Glyph {
	public:
		Glyph() {}

	  Glyph(const glm::vec4& destRect,const glm::vec4& uvRect, GLuint Texture,
					float Depth, const ColorRGBA8& color);
		Glyph(const glm::vec4& destRect,const glm::vec4& uvRect, GLuint Texture,
					float Depth, const ColorRGBA8& color, float angle);

    GLuint texture;
    float depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
  };

  class RenderBatch {
  public:
  RenderBatch(GLuint off,GLuint nV,GLuint t) :
    offset(off), numVertices(nV), texture(t) {};
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
  };

  class SpriteBatch {
  public:
    SpriteBatch();
    ~SpriteBatch();

    void init();
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
							float depth, const ColorRGBA8& color);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
							float depth, const ColorRGBA8& color, float angle);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
							float depth, const ColorRGBA8& color, const glm::vec2& dir);
    void renderBatch();

  private:
    void createRenderBatches();
    void createVertexArray();
    void sortGlyphs();

    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);

    GLuint m_vbo;
    GLuint m_vao;
    GlyphSortType m_sortType;
		std::vector<Glyph*> m_glyphPointers; // For sorting
    std::vector<Glyph> m_glyphs; //Actual glyphs
    std::vector<RenderBatch> m_renderBatches;
  };
}
