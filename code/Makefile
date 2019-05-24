LIBS 		= -lGL -lGLEW -lSDL2
OUTPUT 	= heyo_app
OBJ		= main.o stb_image.o Display.o Shader.o Mesh.o Texture.o obj_loader.o
DEPS = Display.h Mesh.h Shader.h stb_image.h Texture.h Transform.h Camera.h obj_loader.h

%.o: %.c $(DEPS)
	g++ -c $< -o $@

all: $(OBJ)
	g++ $(OBJ) -o $(OUTPUT) $(LIBS)

clean:
	rm -f $(OUTPUT) $(OBJ)
