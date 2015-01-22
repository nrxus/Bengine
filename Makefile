CC=g++
CFLAGS=-c -Wall
CXXFLAGS=-std=gnu++0x
LDFLAGS=-lSDL2 -lGLEW -lGLU -lGL
SOURCES=Sprite.cpp IOManager.cpp GLSLProgram.cpp BengineErrors.cpp picoPNG.cpp ImageLoader.cpp TextureCache.cpp ResourceManager.cpp Window.cpp Bengine.cpp Camera2D.cpp SpriteBatch.cpp InputManager.cpp Timing.cpp SpriteFont.cpp AudioEngine.cpp ParticleBatch2D.cpp ParticleEngine2D.cpp

INCFLAGS=-I.
OBJECTS=$(SOURCES:.cpp=.o)
LINKABLE=libengine.a

all: $(SOURCES) $(LINKABLE)

$(LINKABLE): $(OBJECTS)
	rm -rf $(LINKABLE)
	ar -cvq $(LINKABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCFLAGS) $< -o $@ $(CXXFLAGS)

clean:
	rm -rf *o $(LINKABLE)
