#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <GL\glew.h>
#include <GLM\glm.hpp>
//opengl/glm/sdl
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <GL\glut.h>
#include <glm/glm.hpp>//glm header
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void Initialize();
void Uninitialize();
GLint size();
GLuint vertexbuffer;
std::string exeName;
SDL_Window *window; //named window pointer
SDL_GLContext context;

const std::string strVertexShader(
	
	"#version 140\n"
	
	"in vec4 position;\n"
	"in vec4 color;\n"
	"uniform mat4 modelMatrix;\n"
	"uniform mat4 projectionMatrix;\n"
	"smooth out vec4 theColor;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = projectionMatrix * modelMatrix * position;\n"
	"   theColor = color;\n" 
	"}\n"

								);


const std::string strFragmentShader(
	
	"#version 140\n"
	

	"smooth in vec4 theColor;\n"
	"out vec4 outputColor;\n"
	"void main()\n"
	"{\n"
	"   outputColor = theColor;\n"
	"}\n"

									);



bool done = false;


void drawTriangle()
	//for the triangle only
{
const float trianglevertexData1[] =
{
     0.0f,  0.5f, 
     0.5f, -0.5f,
    -0.5f, -0.5f  
};

GLint size = 3;

glGenBuffers(1, &vertexbuffer);

glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

glBufferData(GL_ARRAY_BUFFER, sizeof(trianglevertexData1), trianglevertexData1, GL_STATIC_DRAW);
}

GLuint object;
float objrot;

void objload(char *objname) //should load the obj
{
	FILE *fp;
	int read;
	char ch;
	GLfloat x,y,z;
	object = glGenLists(1);
	fp=fopen(objname,"r");
	if(fp)
	{
		cout<<("FILE:%s WAS OPENED\n",objname);
	}
	else
	{
		cout<<("FILE: %s COULD NOT BE OPENED\n",objname);
		cout<<("PRESS ANY KEY TO CONTINUE");
		cin.get();
		//exit(1);
	}
	glPointSize(2.0);
	glNewList(object, GL_COMPILE);
		{
			glPushMatrix();
			glBegin(GL_POINTS);
			while(!(feof(fp)))
			{
				read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
				if(read==4&&ch=='v');
				{
					glVertex3f(x,y,z);
				}
			}
			glEnd();
		}
		glPopMatrix();
		glEndList();
		fclose(fp);

}

void shaper(int w,int h)

{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1,1000.0);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-25,25,-2,2,0.1,100);	
	cout<<"reshape used\n";
}

void drawOBJ()
{
	glPushMatrix();
 	glTranslatef(5,-5,-115);
	
 	glColor3f(1.0,0.23,0.27);
 	glScalef(1,1,1);
	glRotatef(objrot,0,2,0);
	glCallList(object);
	glPopMatrix();
	objrot = objrot + 0.6;

	if(objrot>360)
	{
		objrot=objrot-360;
	}

	//cout<<"Drawing OBJ\n";

}


const float vertexData[] = {

    //positions
	 0.25f, 0.25f,   0.25f,1.0f,
	 0.25f, 0.25f,  -0.25f,1.0f,
	-0.25f, 0.25f,   0.25f,1.0f,

	 0.25f, 0.25f,  -0.25f,1.0f,
	-0.25f, 0.25f,  -0.25f,1.0f,
	-0.25f, 0.25f,   0.25f,1.0f,

	 0.25f, -0.25f,  0.25f, 1.0f,
	-0.25f, -0.25f,  0.25f, 1.0f,
	 0.25f, -0.25f, -0.25f, 1.0f,

	 0.25f, -0.25f, -0.25f, 1.0f,
	-0.25f, -0.25f,  0.25f, 1.0f,
	-0.25f, -0.25f, -0.25f, 1.0f,

	-0.25f,  0.25f,  0.25f, 1.0f,
	-0.25f,  0.25f, -0.25f, 1.0f,
	-0.25f, -0.25f, -0.25f, 1.0f,

	-0.25f,  0.25f,  0.25f, 1.0f,
	-0.25f, -0.25f, -0.25f, 1.0f,
	-0.25f, -0.25f,  0.25f, 1.0f,

	 0.25f,  0.25f,  0.25f, 1.0f,
	 0.25f, -0.25f, -0.25f, 1.0f,
	 0.25f,  0.25f, -0.25f, 1.0f,

	 0.25f,  0.25f,  0.25f, 1.0f,
	 0.25f, -0.25f,  0.25f, 1.0f,
	 0.25f, -0.25f, -0.25f, 1.0f,

	 0.25f, -0.25f,  0.25f, 1.0f,
	 0.25f,  0.25f,  0.25f, 1.0f,
	-0.25f,  0.25f,  0.25f, 1.0f,

	 0.25f, -0.25f,  0.25f, 1.0f,
	-0.25f,  0.25f,  0.25f, 1.0f,
	-0.25f, -0.25f,  0.25f, 1.0f,

	 0.25f, -0.25f, -0.25f, 1.0f,
	-0.25f,  0.25f, -0.25f, 1.0f,
	 0.25f,  0.25f, -0.25f, 1.0f,

	 0.25f, -0.25f, -0.25f, 1.0f,
	-0.25f, -0.25f,  0.25f, 1.0f,
	-0.25f, -0.25f, -0.25f, 1.0f,


    //colors

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

};


glm::mat4 ModelMatrix; //matrix for the model to be loaded later
glm::mat4 projectionMatrix; //camera pov matrix
glm::mat4 rotationMatrix; //obvious
glm::mat4 translationMatrix; //again ^^

float rotateSpeed = 5.0f; 
//float rotateSpeed = 1.0f;

glm::vec3 translateSpeedDefault = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 translateSpeed = translateSpeedDefault;
glm::vec3 translateAcceleration = glm::vec3(0.5f, 0.5f, 0.5f);

// GL/GLSL vars

GLuint Program;
GLuint positionLocation;
GLuint colorLocation;
GLuint modelMatrixLocation;
GLuint projectionMatrixLocation;
GLuint vertexBufferObject;
GLuint vao;



void createWidonw()
{
 int beginidWindows = exeName.rfind("\\");
 int beginidLinux = exeName.rfind("/");
 int beginIdx = max(beginidWindows, beginidLinux);
 std::string exeNameEnd = exeName.substr(beginIdx + 1);
 const char *exeNameCStr = exeNameEnd.c_str();

 window = SDL_CreateWindow(exeNameCStr, 100, 100, 600, 600, SDL_WINDOW_OPENGL); //sets peramiters and creats window

	 if(window == nullptr)
	 {
		 std::cout <<"Create window error\n";
		 SDL_Quit();
		 exit(1);
	 }

	 std::cout <<"Window Created\n";

}


void setGLAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	std::cout << "opengl version set to 4.3 (maybe)\n";

}

void createContext()
{
	context = SDL_GL_CreateContext(window);
	if(context==nullptr)
	{
		SDL_DestroyWindow(window);
		std::cout << "context failed to be created\n";
		SDL_Quit();
		exit(1);
	}

	std::cout << "context was created\n";

}


void initGlew()
{
	GLenum rev;

	glewExperimental = GL_TRUE; //hot fix might be able to take out in future (as if)
	rev = glewInit();
	if (GLEW_OK != rev)
	{
		std::cout << "Glew error, horses may be jammed\n";
	}
	else 
	{
		std::cout << "Glew init\n";
	}

}

GLuint createShader(GLenum eShaderType, const std::string &strShaderFile)
{
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);


	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure");
		delete[] strInfoLog;

	}

	return shader;
}


GLuint createProgram(const std::vector<GLuint> &shaderList)

{
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	glLinkProgram(program);

	GLint status;

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == false)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "link failure\n");
		delete[] strInfoLog;
	}

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);
	return program;
}

void initProgram ()
{
	std::vector<GLuint> shaderList;

	//to be added
	shaderList.push_back(createShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, strFragmentShader));

	Program = createProgram(shaderList);
	if (Program == 0)
	{
		std::cout << "creation error\n";
		SDL_QUIT;
		exit(1);
	}
	else
	{
		std::cout << "creation worked\n";
	}

	positionLocation = glGetAttribLocation(Program, "position");
	colorLocation = glGetAttribLocation(Program, "color");
	modelMatrixLocation = glGetUniformLocation(Program, "modelMatrix");
	projectionMatrixLocation = glGetUniformLocation(Program, "projectionMatrix");

	//cleanup crew

	for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

}

void initVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	std::cout<<"object pos created\n";


}

void loadAssets()
{
	initProgram();
	initVertexBuffer();

	glGenVertexArrays(1, &vao); //creates the vertex array object (set as vao)
	glBindVertexArray(vao); //activates
	std::cout << "vao created\n";

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	std::cout <<"assets loaded\n";


}

void secondWindow(void)

{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawOBJ();
	glutSwapBuffers();
}

void updateSimulation(double simLength)
{

	float rotate = (float)simLength * rotateSpeed;

	const glm::vec3 unitX = glm::vec3(1, 0 ,0);
	const glm::vec3 unitY = glm::vec3(0, 1 ,0);
	const glm::vec3 unitZ = glm::vec3(0, 0 ,1);
	const glm::vec3 unit45 = glm::normalize(glm::vec3(0,1,1)); //normalized to stop speed problem
	
	rotationMatrix = glm::rotate(rotationMatrix, rotate, unit45);

	glm::vec3 translate = float(simLength) * translateSpeed;

	translationMatrix = glm::translate(translationMatrix, translate);

	ModelMatrix = translationMatrix * rotationMatrix;

}

void render()
{

	glUseProgram(Program);

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	size_t colorData = sizeof(vertexData) / 2;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//cleanup crew

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}

void handleInput()
{
	SDL_PumpEvents();

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		done = true;
	}

	if (state[SDL_SCANCODE_RSHIFT])
	{

		GLint size = 10;
	}
	else
	{
		GLint size = 3;
	}

	//movement
	if (state[SDL_SCANCODE_SPACE])
	{
		rotateSpeed = 500.0f; //speeds up

	}
	else
	{
		rotateSpeed = 5.0f; //for when the space bar is released to return the speed to normal
	}

	if (state[SDL_SCANCODE_LEFT] != state[SDL_SCANCODE_RIGHT]) //just one pressed
	{
		if (state[SDL_SCANCODE_LEFT]) //left pressed
			translateSpeed.x = translateSpeedDefault.x - translateAcceleration.x;

		else //right pressed
			translateSpeed.x = translateSpeedDefault.x + translateAcceleration.x;
	}

	else
		translateSpeed.x = translateSpeedDefault.x;


	if (state[SDL_SCANCODE_UP] != state[SDL_SCANCODE_DOWN]) //just one pressed
	{
		if (state[SDL_SCANCODE_DOWN]) //left pressed
			translateSpeed.y = translateSpeedDefault.y - translateAcceleration.y;

		else //right pressed
			translateSpeed.y = translateSpeedDefault.y + translateAcceleration.y;
	}
	else
		translateSpeed.y = translateSpeedDefault.y;


}

void cleanupcrew()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	std::cout <<"cleanup crew finished\n";
}

int main(int argc, char *args[])
{
	int objnum;
	int assignmentnum = 0;
	cout<<"Please Input Object loader type:\n1.3D object\n2.Rotating Cube with triangle\n";
	cin>>(assignmentnum);
	switch(assignmentnum){
	case 1:
	
	//obj based


	glutInit(&argc,args);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,450);
	glutInitWindowPosition(20,20);
	glutCreateWindow("Second Screen OBJ Loader");
	glutReshapeFunc(shaper);
	glutDisplayFunc(secondWindow);
	glutIdleFunc(secondWindow);
	cout<<("Please choose what object to load\n1.AK47\n2.car\n3.Teddy\n");
	cin>>(objnum);
	switch (objnum) {
	case 1:
		objload("./objs/ak47.obj");
		cin.get();
		break;
	case 2:
		objload("./objs/car.obj");
		cin.get();
		break;
	case 3:
		objload("./objs/teddy.obj");

	default: cout<<"Incorrect input, please choose the correct input\n";
	}
	glutMainLoop();
	return 0;
	//end of obj based
	break;

	exeName = args[0];
	Initialize();

	case 2:
	// Create displays

	createWidonw();
	setGLAttributes();
	createContext();
	initGlew();
	drawTriangle();
	loadAssets();

	while (!done) //main loop, uses input to loop
	{

		handleInput(); //keys and escape

		updateSimulation(0.02);
		glClear(GL_COLOR_BUFFER_BIT);
		render();
		//drawOBJ();

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
							);
//std::cout <<"triangle setup\n";

glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
 
glDisableVertexAttribArray(0);



		SDL_GL_SwapWindow(window);
	
	}
	cleanupcrew();


	Uninitialize();

	return 0;
	break;
	default:cout<<"Failed to press correct input";
				exit(1);
	}
}

void Initialize()
{

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Initialization failed!" << std::endl;
		exit(1);
	}

	// Initalize SDL Image with support for png and jpg
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG))
	{
		std::cout << "SDL image initialization failed!" << std::endl;
		exit(1);
	}

	// Set OpenGL version 3.3 core profile and enable double buffering
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);	
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

}

void Uninitialize()
{
	SDL_Quit();
}