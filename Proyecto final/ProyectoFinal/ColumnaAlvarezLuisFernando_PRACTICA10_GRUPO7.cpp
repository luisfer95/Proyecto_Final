//Semestre 2020 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************		Columna Alverez Luis Fernando		******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif
//NEW// Keyframes
//Variables de dibujo y manipulacion
float rot1 = 0, rot2 = 0, rotdona = 0;


#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;
int i_max_steps2 = 90;
int i_curr_steps2 = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames

	float rot1;
	float rot2;
	float incrot1;
	float incrot2;
	float rotdona;
	float incdona;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

float R1[MAX_FRAMES] = { 0,90,180,90,0 };
float R2[MAX_FRAMES] = { 0,180,360,180,0 };
float Rdona[MAX_FRAMES] = {0,180,360,180,0};
int FrameIndex2 = 0;			//introducir datos
bool play2 = false;
int playIndex2 = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];


CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture textf; //fachadarosa
CTexture textpiso;//pisito
CTexture textbar;//Barquito
CTexture textmor;//morado
CTexture textmor2;//morado
CTexture textres;//REspaldito sillon
CTexture textcuero;//sillon
CTexture textcojin;//cijincito
CTexture textrosa;//paredes
CTexture textfac;//fachada
CTexture textteja;//teja
CTexture textnar;//techo
CTexture textmora;//morada 
CTexture textlib;//morada 
CTexture textama;//amarilla 
CTexture textver;//verde
CTexture textgris;//gris
CTexture textfon;//telefono
CTexture texttv;//tv
CTexture textmad;//madera
CTexture textneg; //negro
CTexture textazul;//azul
CTexture textnartra;//naranja transparente

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras conoCasa;

CFiguras fig7; //Para el monito

//Figuras de 3D Studio
CModel kit;              //PARA EXPORTAR MODELOS 3DS
CModel llanta;
CModel House;
//Animación del coche
float rotkit = 0.0;
float rotkit1 = 0.0;
float rotkit2 = 0.0;
float movKit = 0.0;
float movkit1 = 0.0;
bool g_fanimacion = false;
bool g_fanimacion1 = false;
bool g_fanimacion2 = false;
bool g_fanimacion3 = false;
bool reversa_fanimacion = false;
void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);
	for (int j = 0; j < MAX_FRAMES; j++) {
		KeyFrame[j].rot1 = R1[j];
		KeyFrame[j].rot2 = R2[j];


		FrameIndex++;
	}
}

void saveFrame2(void)
{

	printf("2frameindex %d\n", FrameIndex2);
	for (int i = 0; i < MAX_FRAMES; i++) {

		KeyFrame[i].rotdona = Rdona[i];



		FrameIndex2++;
	}
}
void resetElements(void)
{
	rot1 = KeyFrame[0].rot1;
	rot2 = KeyFrame[0].rot2;
	

}

void resetElements2(void)
{
	rotdona = KeyFrame[0].rotdona;



}

void interpolation(void)
{
	KeyFrame[playIndex].incrot1 = (KeyFrame[playIndex + 1].rot1 - KeyFrame[playIndex].rot1) / i_max_steps;
	KeyFrame[playIndex].incrot2 = (KeyFrame[playIndex + 1].rot2 - KeyFrame[playIndex].rot2) / i_max_steps;


	

}

void interpolation2(void)
{
	KeyFrame[playIndex2].incdona = (KeyFrame[playIndex2 + 1].rotdona - KeyFrame[playIndex2].rotdona) / i_max_steps;
	



}

			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();
	textpiso.LoadTGA("pisito.tga");
	textpiso.BuildGLTexture();
	textpiso.ReleaseImage();

	textf.LoadTGA("texturaf.tga");
	textf.BuildGLTexture();
	textf.ReleaseImage();

	textbar.LoadTGA("barco.tga");
	textbar.BuildGLTexture();
	textbar.ReleaseImage();

	textmor.LoadTGA("morado.tga");
	textmor.BuildGLTexture();
	textmor.ReleaseImage();

	textmor2.LoadTGA("moradotrans.tga");
	textmor2.BuildGLTexture();
	textmor2.ReleaseImage();

	textres.LoadTGA("respaldo.tga");
	textres.BuildGLTexture();
	textres.ReleaseImage();

	textcuero.LoadTGA("cuero.tga");
	textcuero.BuildGLTexture();
	textcuero.ReleaseImage();

	textcojin.LoadTGA("topcojin.tga");
	textcojin.BuildGLTexture();
	textcojin.ReleaseImage();


	textrosa.LoadTGA("rosita.tga");
	textrosa.BuildGLTexture();
	textrosa.ReleaseImage();

	textfac.LoadTGA("fachada.tga");
	textfac.BuildGLTexture();
	textfac.ReleaseImage();

	textteja.LoadTGA("teja.tga");
	textteja.BuildGLTexture();
	textteja.ReleaseImage();

	textnar.LoadTGA("naranjita.tga");
	textnar.BuildGLTexture();
	textnar.ReleaseImage();

	textmora.LoadTGA("morada.tga");
	textmora.BuildGLTexture();
	textmora.ReleaseImage();

	textlib.LoadTGA("libro1.tga");
	textlib.BuildGLTexture();
	textlib.ReleaseImage();

	textama.LoadTGA("amarilla.tga");
	textama.BuildGLTexture();
	textama.ReleaseImage();

	textver.LoadTGA("verde.tga");
	textver.BuildGLTexture();
	textver.ReleaseImage();

	textgris.LoadTGA("gris.tga");
	textgris.BuildGLTexture();
	textgris.ReleaseImage();

	textfon.LoadTGA("fon.tga");
	textfon.BuildGLTexture();
	textfon.ReleaseImage();

	texttv.LoadTGA("tv.tga");
	texttv.BuildGLTexture();
	texttv.ReleaseImage();

	textmad.LoadTGA("madera.tga");
	textmad.BuildGLTexture();
	textmad.ReleaseImage();

	textneg.LoadTGA("negro.tga");
	textneg.BuildGLTexture();
	textneg.ReleaseImage();

	textazul.LoadTGA("azul.tga");
	textazul.BuildGLTexture();
	textazul.ReleaseImage();

	textnartra.LoadTGA("naranjitatrans.tga");
	textnartra.BuildGLTexture();
	textnartra.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("kitt.3ds");	//Llevar el objeto 3ds a memoria
	//kit.VertexNormals();
	
	llanta._3dsLoad("k_rueda.3ds");

	House._3dsLoad("Dollshouse.3ds");
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].rot1 = 0;
		KeyFrame[i].rot2 = 0;
		KeyFrame[i].rotdona = 0;
		
	}
	objCamera.Position_Camera(10,2.5f,13, 10,2.5f,10, 0, 1, 0);
	saveFrame2();
	saveFrame();
}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}



void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();

		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
			fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			

				if (rotkit == 100)
				{
					g_fanimacion = false;
					reversa_fanimacion = true;
				}
				if (rotkit == 0 && reversa_fanimacion==true) {
					reversa_fanimacion = false;
					g_fanimacion = true;
				}
				
				
					

			glPopMatrix();

			//Para que el comando glColor funcione con iluminacion
			glEnable(GL_COLOR_MATERIAL);
			
			/*glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text4.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();*/

			/*glPushMatrix(); //Camino1
				glTranslatef(23.5,0.0,0.0);
				glScalef(40,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma2(text4.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix(); //Camino2
				glTranslatef(-23.5,0.0,0.0);
				glScalef(40,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma2(text4.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();*/

			/*glPushMatrix(); //Pasto
				glTranslatef(0.0,0.0,-4.0);
				glScalef(87,0.1,87);
				glDisable(GL_LIGHTING);
				fig4.prisma2(text5.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();*/

			glPushMatrix(); //Pasto
				//glTranslatef(0.0,0.0,4.0);
				glScalef(130,0.1,130);
				glDisable(GL_LIGHTING);
				fig4.prisma2(text5.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			/*glPushMatrix(); //Casa01
				glTranslatef(0.0,3.0,7.0);
				glRotatef(90,1,0,0);
				glRotatef(180,0,0,1);
				glScalef(6,5.0,6);
				glDisable(GL_LIGHTING);
				fig5.prisma2(text6.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();*/

			

			glPushMatrix();//inicia casita
					glTranslatef(0, 8.65, 0);
					glScalef(3,1,3);
					glDisable(GL_LIGHTING);
				fig5.prisma3(17,10,12,textrosa.GLindex,textfac.GLindex, textrosa.GLindex, textrosa.GLindex, textpiso.GLindex, textnar.GLindex);
				glPopMatrix();//Termina casita

				glPushMatrix();
				
				glTranslatef(0,-0.2,0);
					glBindTexture(GL_TEXTURE_2D, textteja.GLindex);	
					glBegin(GL_QUADS);
					glTexCoord2f(1,1); glVertex3f(0, 25.3, -18);
					glTexCoord2f(0,1); glVertex3f(0, 25.3, 18);
					glTexCoord2f(0,0); glVertex3f(-15, 17.3, 18);//
					glTexCoord2f(1,0); glVertex3f(-15, 17.3, -18);//
					glEnd();
					glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex3f(15, 17.3, -18);
					glTexCoord2f(1,0); glVertex3f(15, 17.3, 18);
					glTexCoord2f(1,1); glVertex3f(0, 25.3, 18);
					glTexCoord2f(0,1); glVertex3f(0, 25.3, -18);
					glEnd();
					glBegin(GL_TRIANGLES); 
					
					glTexCoord2f(0,0);  glVertex3f(15, 17.3, 18);
					glTexCoord2f(1,0);	glVertex3f(-15, 17.3, 18);
					glTexCoord2f(0.5,1); glVertex3f(0, 25.3, 18);
					glEnd();

					glBegin(GL_TRIANGLES);

					glTexCoord2f(1,0); glVertex3f(15, 17.3, -18);
					glTexCoord2f(0,0); glVertex3f(-15, 17.3, -18);
					glTexCoord2f(0.5,1); glVertex3f(0, 25.3, -18);
					glEnd();
				glPopMatrix();//Termina techo

				glPushMatrix();//Inicia tapita
				glTranslatef(14.5, 7, -0.1);
				fig5.prisma(20, 0.01, 35.8, textrosa.GLindex);
				glPopMatrix();//termina la tappita
				glDisable(GL_LIGHTING);

				glPushMatrix(); //Inicia todo silloncito
				glTranslatef(-11, 0, -2);
				glScalef(1.4, 1, 1.8);
				glPushMatrix(); //inicia Sillon base
				glTranslatef(0, 1, 0);
				fig1.prisma(2, 3, 5, textcuero.GLindex);
					glPopMatrix();//termina Sillon base
					glPushMatrix();//inicia tapa derecha
					
					glTranslatef(0, 1.7, -3);
					fig1.prisma(3.5, 3, 1, textcuero.GLindex);
					glPopMatrix();//termina tapa derecha
					glPushMatrix();//inicia tapa izq
					
					glTranslatef(0, 1.7, 3);
					fig1.prisma(3.5, 3, 1, textcuero.GLindex);
					glPopMatrix();//termina tapa izq
					glPushMatrix();//inicia tapa trasera
					
					glTranslatef(-1, 3.3, 0);
					fig1.prisma(7, 1, 7, textcuero.GLindex);
					glPopMatrix();//termina tapa trasera
					glPushMatrix();//inicia cojin centro
					
					glTranslatef(0.5, 2.5, 0);
					fig1.prisma3(1, 2, 1.6, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex);
					glPopMatrix();//termina cojin centro
					glPushMatrix();//inicia cojin der
					
					glTranslatef(0.5, 2.5, -1.67);
					fig1.prisma3(1, 2, 1.6, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex);
					glPopMatrix();//termina cojin der
					glPushMatrix();//inicia cojin izq
					
					glTranslatef(0.5, 2.5, 1.67);
					fig1.prisma3(1, 2, 1.6, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex, textneg.GLindex, textres.GLindex);
					glPopMatrix();//termina cojin izq
					glPushMatrix();//Inicia cilindro derecho
					glTranslatef(1.6, 3.6, -3);
					glRotatef(90, 0, 0, 1);
						fig2.cilindro(0.7, 3, 20, textcuero.GLindex);
						glPopMatrix();//termina cilindro der
						glPushMatrix();//Inicia cilindro derecho
						glTranslatef(1.6, 3.6, 3);
						glRotatef(90, 0, 0, 1);
						fig2.cilindro(0.7, 3, 20, textcuero.GLindex);
						glPopMatrix();//termina cilindro der
						glPushMatrix();//inicia Bolita derecha
						glTranslatef(1.5, 3.6, 3);
						fig1.esfera(0.7, 20, 20, textcuero.GLindex);
						glPopMatrix();//Termina bolita dereca
						glPushMatrix();//inicia Bolita derecha
						glTranslatef(1.5, 3.6, -3);
						fig1.esfera(0.7, 20, 20, textcuero.GLindex);
						glPopMatrix();//Termina bolita dereca
					glPopMatrix();//termina todo sillon

					glPushMatrix();//Inicia mueblecito de telefono
					//glScalef(1, 1, 1);
					glTranslatef(-7, 0.4, 3);
						glPushMatrix();//cajconcitos inicio
						glTranslatef(-5,4,7);
						glPushMatrix();
						glTranslatef(movkit1, 0, 0);
						fig5.prisma(1.3, 2.8, 7, textmora.GLindex);//cajoncito
						if (movkit1 > 1)
							g_fanimacion2 = false;
						glPopMatrix();
						glTranslatef(0, 1, 0);
						fig5.prisma(0.5, 2.8, 7, textmor.GLindex);
						glTranslatef(0, -3.8, 0);
						fig5.prisma(0.5, 2.8, 7, textmor.GLindex);
						glPushMatrix();
						glTranslatef(1.6, 2.79, 0);
						glPushMatrix();
						glTranslatef(movkit1, 0, 0);
						fig1.esfera(0.4, 20, 20, textres.GLindex);
						glPopMatrix();
						glPopMatrix();
						glPopMatrix(); //fin cajoncitos
						glPushMatrix();//tapita mueblecito derecha
						glRotatef(90, 0,1,0);
						glTranslatef(-3.4, 2.5, -5);
						fig2.prisma(5.4, 0.5, 2.8, textmor.GLindex);
							glPopMatrix();//termina tapita derecha
							glPushMatrix();//inicia tapita izquierda
						
							glRotatef(90, 0, 1, 0);
							glTranslatef(-10.7, 2.5, -5);
							fig2.prisma(5.4, 0.5, 2.8, textmor.GLindex);
							glPopMatrix();//Termina tapita izquierda
							glPushMatrix();//inicia tapita trasera						
							glRotatef(90, 1, 0, 0);
							glTranslatef(-6.6, 7.1, -2.6);
							fig2.prisma(7.8, 0.5, 5.2, textmora.GLindex);
							glPopMatrix();//Termina tapita trasera
							glPushMatrix();//inicia librito derecha
							
							glRotatef(90, 0, 1, 0);
							glTranslatef(-4.0, 2.5, -5);
							fig2.prisma(2.2, 0.5, 2.2, textnar.GLindex);
							glPopMatrix();//Termina librito derecha
							glPushMatrix();//inicia librito enmedio
							
							glRotatef(90, 0, 1, 0);
							glTranslatef(-4.6, 2.5, -5);
							fig2.prisma(2.2, 0.5, 2.2, textlib.GLindex);
							glPopMatrix();//Termina librito enmedio
							glPushMatrix();//inicia librito izquierda
							
							glRotatef(90, 0, 1, 0);
							glTranslatef(-5.2, 2.5, -5);
							fig2.prisma(2.2, 0.5, 2.2, textver.GLindex);
							glPopMatrix();//Termina librito izquierda

							glPushMatrix();//Inicia toda la lamparita
							glTranslatef(-2, 2.1, 4);
							glScalef(0.6, 0.6, 0.6);
							glPushMatrix();//Inicia lamparita basee
							glTranslatef(-4.7, 5.29, 8.9);
							fig2.cilindro(1, 0.3, 20, textama.GLindex);
							glPopMatrix();//Termina lamparita base
							glPushMatrix();//Inicia lamparita cuerpo
							
							glTranslatef(-4.7, 5.6, 8.9);
							fig2.cilindro(0.7, 2.3, 20, textama.GLindex);
							glPopMatrix();//Termina lamparita cuerpo
							
							glPushMatrix();//Inicia lamparita bolita
							glTranslatef(-4.7, 8, 8.9);
							fig1.esfera(0.7, 20, 20, textver.GLindex);
							glPopMatrix();//Termina lamparita bolita
							
							glPushMatrix();//Inicia lamparita penultimo palito
							glTranslatef(-4.7, 8.6, 8.9);
							fig2.cilindro(0.2, 0.7, 20, textver.GLindex);
							glPopMatrix();//Termina lamparita penultimo palito
							
							glPushMatrix();//Inicia lamparita ultimo palito
							glTranslatef(-4.7, 9.3, 8.9);
							fig2.cilindro(0.4, 0.3, 20, textver.GLindex);
							glPopMatrix();//Termina lamparita ultimo palito
							glPushMatrix();//Inicia lamparita cubierta 
							glTranslatef(-4.7, 9.6, 8.9);
							fig1.cono(4, 2, 20, textmor2.GLindex);
							glPopMatrix();//Termina lamparita cubierta
							glPopMatrix(); //Termina toda la lamparita

							glPushMatrix();//Inicia todo telefonito
							glScalef(0.8, 0.8, 0.8);
							glTranslatef(-2, 1.3, 2);
							glPushMatrix();//Inicia base telefonito
						
							glTranslatef(-4.3, 5.52, 5);
							fig3.prisma (0.5, 1.8, 1.8, textgris.GLindex);
							glPopMatrix();//Termina base telefonito

							glPushMatrix();//Inicia teclado telefonito
							
							glTranslatef(-4.3, 6, 5);
							fig3.prisma3(0.5, 1.6, 1.5, textgris.GLindex, textver.GLindex, textgris.GLindex, textgris.GLindex, textgris.GLindex, textfon.GLindex);
							glPopMatrix();//Termina teclado telefonito

							glPushMatrix();//Inicia parte trasera telefonito
							glTranslatef(-4.95, 6.18, 5);
							fig3.prisma(0.8, 0.5, 1.8, textgris.GLindex);
							glPopMatrix();//Termina parte trasera telefonito

							glPushMatrix();//Inicia bocina agarradera telefonito
							glRotatef(90, 1, 0, 0);
							glTranslatef(-5, 3.5, -6.7);
							fig3.cilindro(0.2, 2.9, 20, textgris.GLindex);
							glPopMatrix();//termina agarradera bocina

							glPushMatrix();//Inicia bocina der						
							glTranslatef(-5, 6.2, 3.5);
							fig3.cilindro(0.3, 0.6, 20, textgris.GLindex);
							glPopMatrix();//termina  bocina der

							glPushMatrix();//Inicia bocina izq
							glTranslatef(-5, 6.2, 6.4);
							fig3.cilindro(0.3, 0.6, 20, textgris.GLindex);
							glPopMatrix();//termina  bocina izq

							glPopMatrix(); //Termina todo telefonito

					glPopMatrix();//termina mueblecito de telefono

					glPushMatrix();//Inicia cuadro barquito
					glTranslatef(-14.6, 13, 0);
					glRotatef(rotkit1, 1, 0, 0);
					fig3.prisma(4, 0.1, 6, textbar.GLindex);
					if (rotkit1 > 60)
						g_fanimacion1 = false;
					glPopMatrix();//termina cuadro barquito

					glPushMatrix();//Inicia television
					glPushMatrix();//Inicia Cuadrito mas grande de la tele
					glTranslatef(10, 3, 0);
					fig5.prisma(4, 2.7, 6, textmora.GLindex);
					glPopMatrix(); //Termina cuadrito mas grande de la tele

					glPushMatrix();//Inicia lo que da imagen	
					glTranslatef(8.6, 3, -0.5);
					fig5.prisma(2.3, 0.1, 3.5,texttv.GLindex);
					glPopMatrix(); //Termina lo que da imagen
					
					glPushMatrix();//Inicia bocinita
					glTranslatef(8.6, 2.4, 2);
					fig5.prisma(1.3, 0.1, 0.9, textver.GLindex);
					glPopMatrix(); //Termina bocinita

					glPushMatrix();//Inicia perillita abajo
					glTranslatef(8.6, 3.48, 2);
					fig5.esfera(0.3, 20, 20, textgris.GLindex);
					glPopMatrix(); //Termina perillita abajo

					glPushMatrix();//Inicia perillita arriba
					glTranslatef(8.6, 4.2, 2);
					fig5.esfera(0.3, 20, 20, textgris.GLindex);
					glPopMatrix(); //Termina perillita arriba

					glPushMatrix();//Inicia base antenita
					glTranslatef(9.7, 5.48, -0.9);
					fig5.prisma(0.8, 2, 3.5, textmor.GLindex);
					glPopMatrix(); //Termina base antenita

					glPushMatrix();//Inicia linea base antenita
					glTranslatef(8.7, 5.49, -1.4);
					fig5.prisma(0.4, 0.1, 2, textmora.GLindex);
					glPopMatrix(); //Termina linea base antenita

					glPushMatrix();//Inicia  perillita 1 base antenita
					glTranslatef(8.6, 5.5, 0);
					fig5.esfera(0.2, 20, 20, textver.GLindex);
					glPopMatrix(); //Termina perillita 1 base antenita

					glPushMatrix();//Inicia  perillita 2 base antenita
					glTranslatef(8.6, 5.5, 0.5);
					fig5.esfera(0.2, 20, 20, textver.GLindex);
					glPopMatrix(); //Termina perillita 2 base antenita

					glPushMatrix();//Inicia antenita
					glTranslatef(9.5, 5.9, -1);
					fig5.esfera(0.8, 20, 20, textmor.GLindex);
					glPopMatrix(); //Termina  antenita
					glPushMatrix();//inician pata 1
					glTranslatef(9.2, 1, 2.2);
					glRotatef(180, 1, 0, 0);
					fig1.cono(1, 0.5, 20, textmad.GLindex);
					glPopMatrix();//Terminan pata1 
					glPushMatrix();//inician pata 2
					glTranslatef(9.2, 1, -2.2);
					glRotatef(180, 1, 0, 0);
					fig1.cono(1, 0.5, 20, textmad.GLindex);
					glPopMatrix();//Terminan pata2
					glPushMatrix();//inician pata 3
					glTranslatef(10.7, 1, -2.2);
					glRotatef(180, 1, 0, 0);
					fig1.cono(1, 0.5, 20, textmad.GLindex);
					glPopMatrix();//Terminan pata3
					glPushMatrix();//inician pata 3
					glTranslatef(10.7, 1, 2.2);
					glRotatef(180, 1, 0, 0);
					fig1.cono(1, 0.5, 20, textmad.GLindex);
					glPopMatrix();//Terminan pata3
					glPopMatrix();//Termina television
					glPushMatrix();//inician antenitas
					glTranslatef(9.5, 6.5, -1);
					glRotatef(-45 -rotkit2, 1, 0, 0);
					fig1.cilindro(0.05, 2, 20,textneg.GLindex);
					glRotatef(90 +2*rotkit2, 1, 0, 0);
					fig1.cilindro(0.05, 2, 20, textneg.GLindex);
					if (rotkit2 >30)
						g_fanimacion3 = false;
						glPopMatrix();//terminanan antenitas
	
						
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					glPushMatrix();//Inicia Lamparota
						
						glTranslatef(-11, 0, -11.7);
						
						glPushMatrix();//inicia base lamparota	
							glTranslatef(0, 0, 0);
							fig3.cono(0.9, 2, 20, textmor.GLindex);
						glPopMatrix();//termina base lamparota
						glRotatef(rot1, 0, 1, 0);
						glPushMatrix();//Inicia palo lamparota
							glTranslatef(0, 0.9, 0);
							fig3.cilindro(0.2, 8.2, 20, textmor.GLindex);
						glPopMatrix();//termina palo lamparota



						glPushMatrix();//Inicia primer bolita lamparota
							glTranslatef(0, 9.3, 0);
							fig3.esfera(0.4, 20, 20, textmora.GLindex);
						glPopMatrix();//termina primer bolita lamparota

						glPushMatrix();//Inicia  palo inclinado lamparota

							glTranslatef(0, 9.3, 0);
							glRotatef(90, 1, 0, 0);
							fig3.cilindro(0.2, 2, 20, textazul.GLindex);
						glPopMatrix();//termina palo inclinado lamparota

						glPushMatrix();//Inicia segunda bolita lamparota

							glTranslatef(0, 9.3, 2);
							fig3.esfera(0.4, 20, 20, textmora.GLindex);
						glPopMatrix();//termina segunda bolita lamparota

						glPushMatrix();//Inicia segundo palo vertical lamparota
							glTranslatef(0, 9.3, 2);
						fig3.cilindro(0.2, 2, 20, textazul.GLindex);
						glPopMatrix();//termina segundo palo vertical lamparota
		
						glPushMatrix();//Inicia tercer bolita lamparota
							glTranslatef(0, 11.3, 2);
							glRotatef(rot2, 0, 0, 1);
							fig3.esfera(0.4, 20, 20, textmora.GLindex);
						glPopMatrix();//termina tercer  bolita lamparota

						glPushMatrix();//Inicia segundo palo inclinado lamparota
							glTranslatef(0, 11.3, 2);
							glRotatef(rot2, 0, 0, 1);
							glRotatef(90, 1, 0, 0);
					fig3.cilindro(0.2, 3, 20, textazul.GLindex);
					glPopMatrix();//termina segundo palo inclinado lamparota

					glPushMatrix();//Inicia cono
					glTranslatef(0, 11, 5.4);
					glRotatef(rot2, 0, 0, 1);
					glTranslatef(0, -1, 0);
					fig1.cono(4, 1.5, 20, textnartra.GLindex);
					glPopMatrix();//termina cono
					glPopMatrix(); //termina lamparota

					glPushMatrix();//inicia Dona
					glTranslatef(0, 0, -35);
					fig1.cilindro(1, 35, 20, textgris.GLindex);
					glTranslatef(0, 41, 0);
					glEnable(GL_LIGHTING);
					glColor3f(1, 0, 1);
					glRotatef(rotdona, 0, 1, 0);
					glutSolidTorus(3, 6, 20, 20);
						glPopMatrix();//Termina Dona
						

					
					glEnable(GL_LIGHTING);
				glPopMatrix();  
				glEnable(GL_LIGHTING);
				
			glPopMatrix();

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glColor3f(1.0,0.0,0.0);
		pintaTexto(-12,12.0,-14.0,(void *)font,"Proyecto Final Labo");
		pintaTexto(-12,10.5,-14,(void *)font,"Salita de los Simpsons");
		glColor3f(1.0,1.0,1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;


	if(g_fanimacion)
	{
		movKit +=1.0;
		rotkit +=1.0;
	}
	if (g_fanimacion1)
	{
	
		rotkit1 += 1.0;
	}
	if (g_fanimacion2)
	{

		movkit1 += 1.0;
	}
	if (g_fanimacion3)
	{

		rotkit2 += 1.0;
	}
	if (reversa_fanimacion) {
		movKit -= 1.0;
		rotkit -= 1.0;
	}

	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			rot1 += KeyFrame[playIndex].incrot1;
			rot2 += KeyFrame[playIndex].incrot2;



			i_curr_steps++;
		}
	}

	if (play2)
	{

		if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
		{
			playIndex2++;
			if (playIndex2 > FrameIndex2 - 2)	//end of total animation?
			{
				printf("termina animdona\n");
				playIndex2 = 0;
				play2 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps2 = 0; //Reset counter
				//Interpolation
				interpolation2();

			}
		}
		else
		{
			//Draw animation
			rotdona += KeyFrame[playIndex2].incdona;


			i_curr_steps2++;
		}
	}

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;


		case 'u':
		case 'U':
			if (play2 == false && (FrameIndex2 > 1))
			{

				resetElements2();
				//First Interpolation				
				interpolation2();

				play2 = true;
				playIndex2 = 0;
				i_curr_steps2 = 0;
			}
			else
			{
				play2 = false;
			}
			break;

		case 'l':
		case 'L':
			if (play == false && (FrameIndex > 1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
			{
				play = false;
			}
			break;

		case'm':
			rot1++;
			break;
		case'M':
			rot1--;
			break;
		case'z':
			rot2++;
			break;
		case'Z':
			rot2--;
			break;
		case't':
			rotdona++;
			break;
		case'T':
			rotdona--;
			printf("%f", rotdona);
			break;
		case ' ':		//Poner algo en movimiento
			g_fanimacion^= true; //Activamos/desactivamos la animacíon
			break;
		case '1':		//Poner algo en movimiento
			g_fanimacion1 ^= true; //Activamos/desactivamos la animacíon
			break;
		case '2':		//Poner algo en movimiento
			g_fanimacion2 ^= true; //Activamos/desactivamos la animacíon
			break;
		case '3':		//Poner algo en movimiento
			g_fanimacion3 ^= true; //Activamos/desactivamos la animacíon
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;

  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, 
	int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 10"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion ); //FUNCION QUE SE MANDA A LLAMAR A SI MISMA
  glutMainLoop        ( );          // 

  return 0;
}
