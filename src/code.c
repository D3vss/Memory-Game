#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "extern.h"

//********************************************************************************************************************//
	
//Definition des element de gtk: les fenetres, les buttons...								


GtkStack *stack;					//stack: un contenaire de gtk, qui permet d'inserer plusieurs pages dedans.
GtkWidget *p1;						//les pi sont les pages a l'interieur du stack
GtkWidget *p2;
GtkWidget *p3;
GtkWidget *p4;
GtkWidget *p5;
GtkWidget *p6;
GtkWidget *p7;
GtkWidget *p8;						
GtkWidget *p9;							
GtkWidget *p10;							
GtkWidget *p11;							
GtkWidget *p12;						
GtkWidget *p13;						//
GtkWidget *window;
GtkWidget *button;					
GtkWidget *okinfo;					
GtkWidget *Grid;
GtkWindow *infowin;
GtkWindow *help_popup;
GtkWindow *settings_popup;
GtkWindow *settings_ingame;


//********************************************************************************************************************//

//Mode du jeu: 0 si le mode est single player ; 1 si le mode est multiplayer

int gamemode ;
int playercurrent=1;

//********************************************************************************************************************//

//Definitions des elements permettant d'afficher, enregistrer et manipuler les scores:    

typedef struct Joueur
{
    char nom[60];
    int score;
    struct Joueur *suivant;
} Joueur;

Joueur players;

GtkWidget *scoreboardG;
GtkWidget *scoreboard;
GtkWidget *scoreboard1;
GtkWidget *scoreboard2;
GtkWindow *scoreboard_window;
GtkWidget *finalscore;


GtkWidget *ep1score;
GtkWidget *ep2score;

GtkWidget *mp1score;
GtkWidget *mp2score;

GtkWidget *hp1score;
GtkWidget *hp2score;


GtkWidget *esplayer;
GtkWidget *msplayer;
GtkWidget *hsplayer;

GtkWidget *eplayer1;
GtkWidget *eplayer2;

GtkWidget *mplayer1;
GtkWidget *mplayer2;

GtkWidget *hplayer1;
GtkWidget *hplayer2;

GtkWidget *textbox;
GtkWidget *textbox2;
GtkWidget *textbox3;

gchar *PlayerName;
gchar *PlayerName1;
gchar *PlayerName2;


GtkWidget *player1;
GtkWidget *player2;
GtkWidget *player3;
GtkWidget *player4;
GtkWidget *player5;

GtkWidget *score1;
GtkWidget *score2;
GtkWidget *score3;
GtkWidget *score4;
GtkWidget *score5;


int whichplayer=0;


int scorep1=0,scorep2=0;

int ffscore;
int score=0;
char scorebuff[250];
int eflipped=0;
int mflipped=0;
int hflipped=0;

char scorebuff1m[250];

char scorebuff2m[250];

char fscore[3];

FILE *fichier;
//********************************************************************************************************************//

//On a utiliser la librairie SDL2 pour integrer le son:					

Mix_Music *background;  // La musique en arrier plan

Mix_Chunk *click;		//Les effets du clique
Mix_Chunk *success;
Mix_Chunk *wrong;
Mix_Chunk *choose;


//********************************************************************************************************************//

//Chaque carte sur notre grille est representée par un boutton:

//Les cartes du niveau:

// EASY 
GtkWidget	*eimg1;
GtkWidget	*eimg2;
GtkWidget	*eimg3;
GtkWidget	*eimg4;
GtkWidget	*eimg5;
GtkWidget	*eimg6;

//MEDIUM
GtkWidget	*mimg1;
GtkWidget	*mimg2;
GtkWidget	*mimg3;
GtkWidget	*mimg4;
GtkWidget	*mimg5;
GtkWidget	*mimg6;
GtkWidget	*mimg7;
GtkWidget	*mimg8;
GtkWidget	*mimg9;
GtkWidget	*mimg10;
GtkWidget	*mimg11;
GtkWidget	*mimg12;

//HARD
GtkWidget	*himg1;
GtkWidget	*himg2;
GtkWidget	*himg3;
GtkWidget	*himg4;
GtkWidget	*himg5;
GtkWidget	*himg6;
GtkWidget	*himg7;
GtkWidget	*himg8;
GtkWidget	*himg9;
GtkWidget	*himg10;
GtkWidget	*himg11;
GtkWidget	*himg12;
GtkWidget	*himg13;
GtkWidget	*himg14;
GtkWidget	*himg15;
GtkWidget	*himg16;



//***multi

// EASY 
GtkWidget	*meimg1;
GtkWidget	*meimg2;
GtkWidget	*meimg3;
GtkWidget	*meimg4;
GtkWidget	*meimg5;
GtkWidget	*meimg6;

//MEDIUM
GtkWidget	*mmimg1;
GtkWidget	*mmimg2;
GtkWidget	*mmimg3;
GtkWidget	*mmimg4;
GtkWidget	*mmimg5;
GtkWidget	*mmimg6;
GtkWidget	*mmimg7;
GtkWidget	*mmimg8;
GtkWidget	*mmimg9;
GtkWidget	*mmimg10;
GtkWidget	*mmimg11;
GtkWidget	*mmimg12;

//HARD
GtkWidget	*mhimg1;
GtkWidget	*mhimg2;
GtkWidget	*mhimg3;
GtkWidget	*mhimg4;
GtkWidget	*mhimg5;
GtkWidget	*mhimg6;
GtkWidget	*mhimg7;
GtkWidget	*mhimg8;
GtkWidget	*mhimg9;
GtkWidget	*mhimg10;
GtkWidget	*mhimg11;
GtkWidget	*mhimg12;
GtkWidget	*mhimg13;
GtkWidget	*mhimg14;
GtkWidget	*mhimg15;
GtkWidget	*mhimg16;







//Elements for our levels

int nbCol, nbLigne, nbCases;
int occ[16];
int max=8;

//********************************************************************************************************************//

//Ces elements vont etre utiliser dans des prochaines fonction qui permet de tourner deux cartes fausses.

GtkButton **	ListButtn;

bool entre = false;
int compteur =0;
int NameNumber;


struct ListCpm {
	int NumberName1;
	int NumberName2;
};

typedef struct ListCpm ListCpm;

ListCpm ListCaseCmp;

//********************************************************************************************************************//

//Definition d'un compteur qui va faire le countdown de 5s qui permettra au joueur de se rappeller l'ordre des cartes.

//Pour afficher le countdown, on a utilisé des elements de gtk appelés "label"
GtkWidget *labelg;
GtkWidget *label;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *label3;
GtkWidget *label4;
GtkWidget *label5;


bool timer_started=false;
bool timer_paused=true;
int sec=6;
char buff[250];
char countdown[6]={'5','4','3','2','1',' '};
int i=0;


//cette fonction met à jour le "label" chaque 1s, et utilise la notion de la recursivité.

void update_label(GtkWidget *labelg)
{
	if(timer_started==true && timer_paused==false)
	{
			
		    snprintf(buff, 255, "%c", countdown[i]);	
			gtk_label_set_text(labelg, buff);
			i++;
			g_timeout_add_seconds(1,update_label,labelg);


	}	
	if(timer_started==true && timer_paused==true)

	{
		gtk_label_set_text(labelg, buff);
		return	false;

	}

	return false;
}

//Cette fonction permet de commencer le countdown

void start_timer()
{

	if(timer_started==true)
	{	
		return;
	}
	timer_paused=false;
	timer_started=true;
	g_timeout_add_seconds(1,update_label,labelg);
		

	
}

//Cette fonction permet de mettre en pause le countdown

void pause_timer()
{
	if(timer_paused==true)
	{
		return;
	}

	timer_paused=true;
	timer_started=false;
}

//Cette fonction permet de recommencer le countdown, elle utiliser une fois on recommence une partie ou lorsqu'on lance une nouvelle.

void reset_timer()
{
	timer_started=false;
	timer_paused=true;
	sec=6;
	i=0;
	gtk_label_set_text(labelg, "Ready");
}
                                                                                        
//***********************************************************************************************************************************//



//Generer des nombre aleatoires:
//Lors de la resolution de notre probleme, nous avions besoin d'une fonction qui genere n nombre aleatoire, entre 1 et n et qui se repete exactement 2 fois.
//C'est exactement que font ses fonctions: 

void NombresAleatoire()
{
	for(int i=0;i<=(nbCases/2);i++)
    {
        occ[i]=0;
	}
}


int** randooooom()

{	

	srand(time(NULL));
	NombresAleatoire();

    int **T= (int**)calloc(nbLigne,sizeof(int*));

	for(int i =0;i<nbLigne;i++)
		{

		T[i] = (int*)calloc(nbCol,sizeof(int));
    
		}

	
	int i, j, k = 0;
    for (i = 0; i < nbLigne; i++)
		for(j = 0; j < nbCol; j++)
        {
            do{
                k = 1 + (rand() % (nbCases/2));
            } while (occ[k - 1] >= 2);
            occ[k - 1]++;
            T[i][j] = k;
        }


        return T;
}

//********************************************************************************************************************//

//Cette structure represente une image qui va etre placé sur la table, elle doit etre aleatoire, c'est pour cela on a inclut le nombre aleatoire generé
// et la direction vers une image dans notre database

struct tswira
{
	int a;				
	char ipath[100];
					
};

typedef struct tswira tswira;

//********************************************************************************************************************//


//Creation d'une liste contenant les directions de toutes les images 

struct pathimg
{
	char path[100];
};
typedef struct pathimg pathimg;


//********************************************************************************************************************//

//Ceux sont des listes de type "tswira" qu'on va remplir par des images, dans un ordre aleatoires et qu'on va afficher prochainement sur la grille. Chaque liste represente un niveau

tswira etswiracase[6];  //e pour easy
tswira mtswiracase[12]; //m pour medium
tswira htswiracase[16]; //h pour hard


//C'est la plus importante fonction dans le jeu, elle permet de remplir les listes defini ci-dessus

 create_struct()
{
	int k=0;

	pathimg listeimg[max];

	strcpy(listeimg[0].path,"/home/dvss/Desktop/Memory Game/assets/V2/tiger.png");
	strcpy(listeimg[1].path,"/home/dvss/Desktop/Memory Game/assets/V2/monkey.png");
	strcpy(listeimg[2].path,"/home/dvss/Desktop/Memory Game/assets/V2/snake.png");
	strcpy(listeimg[3].path,"/home/dvss/Desktop/Memory Game/assets/V2/dragon.png");
	strcpy(listeimg[4].path,"/home/dvss/Desktop/Memory Game/assets/V2/rat.png");
	strcpy(listeimg[5].path,"/home/dvss/Desktop/Memory Game/assets/V2/rabbit.png");
	strcpy(listeimg[6].path,"/home/dvss/Desktop/Memory Game/assets/V2/horse.png");
	strcpy(listeimg[7].path,"/home/dvss/Desktop/Memory Game/assets/V2/dog.png");


	int **tab=randooooom();
	for(int i=0;i<nbLigne;i++)
	{
		for(int j=0;j<nbCol;j++)
		{	

			tswira img;
			img.a=tab[i][j];
			strcpy(img.ipath,listeimg[(img.a)-1].path);
			printf("%s\n",img.ipath);
			
		if(nbCases==6)	
			{etswiracase[k]=img;
			k++;

			}

		if(nbCases==12)
			{mtswiracase[k]=img;
			k++;
			}

		if(nbCases==16)
			{htswiracase[k]=img;
			k++;
			}
		}
	}
	
}


//********************************************************************************************************************//


//*********************************************************                      MAIN                  ***********************************************************//


int main()
{	
	//Sound effects
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ;
	background = Mix_LoadMUS("/home/dvss/Desktop/Memory Game/sound/back1.mp3");
	click=Mix_LoadWAV("/home/dvss/Desktop/Memory Game/sound/click2.wav");
	success=Mix_LoadWAV("/home/dvss/Desktop/Memory Game/sound/success.wav");
	wrong=Mix_LoadWAV("/home/dvss/Desktop/Memory Game/sound/wrong.wav");
	choose=Mix_LoadWAV("/home/dvss/Desktop/Memory Game/sound/click.wav");
	Mix_PlayMusic(background, -1);





	///******************
	GtkBuilder *builder;
	gtk_init(NULL,NULL);

	ListButtn = (GtkButton **)malloc(2*sizeof(GtkButton*));
	ListCpm ListCaseCmp;



	builder=gtk_builder_new_from_file ("v2.glade");       
	
	Grid=GTK_WIDGET(gtk_builder_get_object(builder , "Grid"));
	window=GTK_WIDGET(gtk_builder_get_object(builder , "window"));

	infowin=GTK_WIDGET(gtk_builder_get_object(builder , "infowin"));
	help_popup=GTK_WIDGET(gtk_builder_get_object(builder , "help_popup"));
	settings_popup=GTK_WIDGET(gtk_builder_get_object(builder , "settings_popup"));
	settings_ingame=GTK_WIDGET(gtk_builder_get_object(builder , "settings_ingame"));
	
	//timer

    label =GTK_WIDGET(gtk_builder_get_object(builder , "label"));
    label1 =GTK_WIDGET(gtk_builder_get_object(builder , "label1"));
    label2 =GTK_WIDGET(gtk_builder_get_object(builder , "label2"));
    label3 =GTK_WIDGET(gtk_builder_get_object(builder , "label3"));
    label4 =GTK_WIDGET(gtk_builder_get_object(builder , "label4"));
    label5 =GTK_WIDGET(gtk_builder_get_object(builder , "label5"));


    //score

    scoreboard=GTK_WIDGET(gtk_builder_get_object(builder , "scoreboard"));
    scoreboard1=GTK_WIDGET(gtk_builder_get_object(builder , "scoreboard1"));
    scoreboard2=GTK_WIDGET(gtk_builder_get_object(builder , "scoreboard2"));


    ep1score=GTK_WIDGET(gtk_builder_get_object(builder , "ep1score"));
    ep2score=GTK_WIDGET(gtk_builder_get_object(builder , "ep2score"));

    mp1score=GTK_WIDGET(gtk_builder_get_object(builder , "mp1score"));
    mp2score=GTK_WIDGET(gtk_builder_get_object(builder , "mp2score"));

    hp1score=GTK_WIDGET(gtk_builder_get_object(builder , "hp1score"));
    hp2score=GTK_WIDGET(gtk_builder_get_object(builder , "hp2score"));

    finalscore=GTK_WIDGET(gtk_builder_get_object(builder , "finalscore"));

    scoreboard_window=GTK_WIDGET(gtk_builder_get_object(builder , "scoreboard_window"));


    //display score

    player1=GTK_WIDGET(gtk_builder_get_object(builder , "player1"));
	player2=GTK_WIDGET(gtk_builder_get_object(builder , "player2"));
	player3=GTK_WIDGET(gtk_builder_get_object(builder , "player3"));
	player4=GTK_WIDGET(gtk_builder_get_object(builder , "player4"));
	player5=GTK_WIDGET(gtk_builder_get_object(builder , "player5"));

	score1=GTK_WIDGET(gtk_builder_get_object(builder , "score1"));
	score2=GTK_WIDGET(gtk_builder_get_object(builder , "score2"));
	score3=GTK_WIDGET(gtk_builder_get_object(builder , "score3"));
	score4=GTK_WIDGET(gtk_builder_get_object(builder , "score4"));
	score5=GTK_WIDGET(gtk_builder_get_object(builder , "score5"));

    //NAme display

    esplayer=GTK_WIDGET(gtk_builder_get_object(builder , "esplayer"));
    msplayer=GTK_WIDGET(gtk_builder_get_object(builder , "msplayer"));
    hsplayer=GTK_WIDGET(gtk_builder_get_object(builder , "hsplayer"));


    eplayer1=GTK_WIDGET(gtk_builder_get_object(builder , "eplayer1"));
    eplayer2=GTK_WIDGET(gtk_builder_get_object(builder , "eplayer2"));

    mplayer1=GTK_WIDGET(gtk_builder_get_object(builder , "mplayer1"));
    mplayer2=GTK_WIDGET(gtk_builder_get_object(builder , "mplayer2"));

    hplayer1=GTK_WIDGET(gtk_builder_get_object(builder , "hplayer1"));
    hplayer2=GTK_WIDGET(gtk_builder_get_object(builder , "hplayer2"));

    textbox=GTK_WIDGET(gtk_builder_get_object(builder , "textbox"));
    textbox2=GTK_WIDGET(gtk_builder_get_object(builder , "textbox2"));
    textbox3=GTK_WIDGET(gtk_builder_get_object(builder , "textbox3"));

    //char fscore[50]=gtk_label_get_text(scoreboardG);



    //*******************


	stack=GTK_STACK(gtk_builder_get_object(builder , "stack"));
	p1=GTK_WIDGET(gtk_builder_get_object(builder , "p1"));
	p2=GTK_WIDGET(gtk_builder_get_object(builder , "p2"));
	p3=GTK_WIDGET(gtk_builder_get_object(builder , "p3"));
	p4=GTK_WIDGET(gtk_builder_get_object(builder , "p4"));
	p5=GTK_WIDGET(gtk_builder_get_object(builder , "p5"));
	p6=GTK_WIDGET(gtk_builder_get_object(builder , "p6"));
	p7=GTK_WIDGET(gtk_builder_get_object(builder , "p7"));
	p8=GTK_WIDGET(gtk_builder_get_object(builder , "p8"));
	p9=GTK_WIDGET(gtk_builder_get_object(builder , "p9"));
	p10=GTK_WIDGET(gtk_builder_get_object(builder , "p10"));
	p11=GTK_WIDGET(gtk_builder_get_object(builder , "p11"));
	p12=GTK_WIDGET(gtk_builder_get_object(builder , "p12"));
	p13=GTK_WIDGET(gtk_builder_get_object(builder , "p13"));


	okinfo=GTK_WIDGET(gtk_builder_get_object(builder , "okinfo"));




//Images of the easy level (6)

	eimg1=GTK_WIDGET(gtk_builder_get_object(builder , "eimg1"));
	eimg2=GTK_WIDGET(gtk_builder_get_object(builder , "eimg2"));
	eimg3=GTK_WIDGET(gtk_builder_get_object(builder , "eimg3"));
	eimg4=GTK_WIDGET(gtk_builder_get_object(builder , "eimg4"));
	eimg5=GTK_WIDGET(gtk_builder_get_object(builder , "eimg5"));
	eimg6=GTK_WIDGET(gtk_builder_get_object(builder , "eimg6"));

//Images of the medium level (12)

	mimg1=GTK_WIDGET(gtk_builder_get_object(builder , "mimg1"));
	mimg2=GTK_WIDGET(gtk_builder_get_object(builder , "mimg2"));
	mimg3=GTK_WIDGET(gtk_builder_get_object(builder , "mimg3"));
	mimg4=GTK_WIDGET(gtk_builder_get_object(builder , "mimg4"));
	mimg5=GTK_WIDGET(gtk_builder_get_object(builder , "mimg5"));
	mimg6=GTK_WIDGET(gtk_builder_get_object(builder , "mimg6"));
	mimg7=GTK_WIDGET(gtk_builder_get_object(builder , "mimg7"));
	mimg8=GTK_WIDGET(gtk_builder_get_object(builder , "mimg8"));
	mimg9=GTK_WIDGET(gtk_builder_get_object(builder , "mimg9"));
	mimg10=GTK_WIDGET(gtk_builder_get_object(builder , "mimg10"));
	mimg11=GTK_WIDGET(gtk_builder_get_object(builder , "mimg11"));
	mimg12=GTK_WIDGET(gtk_builder_get_object(builder , "mimg12"));

//Images of the hard level (16)

	himg1=GTK_WIDGET(gtk_builder_get_object(builder , "himg1"));
	himg2=GTK_WIDGET(gtk_builder_get_object(builder , "himg2"));
	himg3=GTK_WIDGET(gtk_builder_get_object(builder , "himg3"));
	himg4=GTK_WIDGET(gtk_builder_get_object(builder , "himg4"));
	himg5=GTK_WIDGET(gtk_builder_get_object(builder , "himg5"));
	himg6=GTK_WIDGET(gtk_builder_get_object(builder , "himg6"));
	himg7=GTK_WIDGET(gtk_builder_get_object(builder , "himg7"));
	himg8=GTK_WIDGET(gtk_builder_get_object(builder , "himg8"));
	himg9=GTK_WIDGET(gtk_builder_get_object(builder , "himg9"));
	himg10=GTK_WIDGET(gtk_builder_get_object(builder , "himg10"));
	himg11=GTK_WIDGET(gtk_builder_get_object(builder , "himg11"));
	himg12=GTK_WIDGET(gtk_builder_get_object(builder , "himg12"));
	himg13=GTK_WIDGET(gtk_builder_get_object(builder , "himg13"));
	himg14=GTK_WIDGET(gtk_builder_get_object(builder , "himg14"));
	himg15=GTK_WIDGET(gtk_builder_get_object(builder , "himg15"));
	himg16=GTK_WIDGET(gtk_builder_get_object(builder , "himg16"));

//****************************************************************

	//Images of the easy level (6)

	meimg1=GTK_WIDGET(gtk_builder_get_object(builder , "meimg1"));
	meimg2=GTK_WIDGET(gtk_builder_get_object(builder , "meimg2"));
	meimg3=GTK_WIDGET(gtk_builder_get_object(builder , "meimg3"));
	meimg4=GTK_WIDGET(gtk_builder_get_object(builder , "meimg4"));
	meimg5=GTK_WIDGET(gtk_builder_get_object(builder , "meimg5"));
	meimg6=GTK_WIDGET(gtk_builder_get_object(builder , "meimg6"));

//Images of the medium level (12)

	mmimg1=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg1"));
	mmimg2=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg2"));
	mmimg3=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg3"));
	mmimg4=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg4"));
	mmimg5=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg5"));
	mmimg6=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg6"));
	mmimg7=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg7"));
	mmimg8=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg8"));
	mmimg9=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg9"));
	mmimg10=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg10"));
	mmimg11=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg11"));
	mmimg12=GTK_WIDGET(gtk_builder_get_object(builder , "mmimg12"));

//Images of the hard level (16)

	mhimg1=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg1"));
	mhimg2=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg2"));
	mhimg3=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg3"));
	mhimg4=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg4"));
	mhimg5=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg5"));
	mhimg6=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg6"));
	mhimg7=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg7"));
	mhimg8=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg8"));
	mhimg9=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg9"));
	mhimg10=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg10"));
	mhimg11=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg11"));
	mhimg12=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg12"));
	mhimg13=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg13"));
	mhimg14=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg14"));
	mhimg15=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg15"));
	mhimg16=GTK_WIDGET(gtk_builder_get_object(builder , "mhimg16"));


	gtk_builder_connect_signals(builder,NULL);

	gtk_widget_show_all(window);
    gtk_main();

return 0;

}

//********************************************************************************************************************//




//************************************Definitions des fonctions*****************************************//

//Activer le click sur le boutton "help"

void on_helpbutton_clicked(GtkButton *button)
{
	gtk_widget_show_all(help_popup); 
	//l'effet sonore
    Mix_PlayChannel(-1, click, 0);

    if (strcmp(gtk_widget_get_name(button),"helpokbutton")== 0)
    {
    	    gtk_widget_hide(help_popup);


    	    //l'effet sonore
       		Mix_PlayChannel(-1, click, 0);

    }

}


//Activer le click sur le boutton "settings"

void on_settingsbutton_clicked(GtkButton *button)
{
	gtk_widget_show_all(settings_popup);
	//l'effet sonore
    Mix_PlayChannel(-1, click, 0);

    if (strcmp(gtk_widget_get_name(button),"settingsokbutton")== 0)
    {
    	    gtk_widget_hide(settings_popup);
    	    //l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
    }
        if (strcmp(gtk_widget_get_name(button),"leavebutton")== 0)
    {
    	    gtk_widget_destroy(settings_popup);
    	    gtk_widget_destroy(window);
    	    Mix_FreeMusic(background);
			Mix_FreeChunk(click);
			Mix_CloseAudio();

    }

    if (strcmp(gtk_widget_get_name(button),"home")== 0)
    {	

		gtk_stack_set_visible_child (stack,p1);
  	    gtk_widget_hide(settings_popup);

    	//l'effet sonore
       	Mix_PlayChannel(-1, click, 0);
    }


}

//Activer le click sur le boutton "settings" au cours d'une partie

void on_settingsingame_clicked(GtkButton *button)
{	

	//pause_timer();
	if (strcmp(gtk_widget_get_name(button),"settingsbutton2")== 0)
    {
    	    gtk_widget_show_all(settings_ingame);
    	    //l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
    }
	

    if (strcmp(gtk_widget_get_name(button),"settingsokbutton2")== 0)
    {		
    		start_timer();
    	    gtk_widget_hide(settings_ingame);
    	    //l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
    }
        if (strcmp(gtk_widget_get_name(button),"leavebutton2")== 0)
    {
    	    gtk_widget_destroy(settings_ingame);
    	    gtk_widget_destroy(window);
    	    Mix_FreeMusic(background);
			Mix_FreeChunk(click);
			Mix_CloseAudio();

    }


	if (strcmp(gtk_widget_get_name(button),"retry")== 0 && gamemode==0)
    {
		gtk_stack_set_visible_child (stack,p3);
		pause_timer();
		reset_timer();
    	gtk_widget_hide(settings_ingame);
   		score=0;
		//l'effet sonore
       	Mix_PlayChannel(-1, click, 0);


    }
    if (strcmp(gtk_widget_get_name(button),"retry")== 0 && gamemode==1)
    {
		gtk_stack_set_visible_child (stack,p8);
		pause_timer();
		reset_timer();
    	gtk_widget_hide(settings_ingame);
    	score=0;
		//l'effet sonore
       	Mix_PlayChannel(-1, click, 0);


    }

}


//Cette fonction permet de choisir le niveau


void on_button_clicked(GtkButton *button)
{	
	if(strcmp(gtk_widget_get_name(button),"play")==0)
	{	
		gtk_stack_set_visible_child (stack,p7);
		//l'effet sonore
       	Mix_PlayChannel(-1, click, 0);
	}

	if(strcmp(gtk_widget_get_name(button),"ok")==0)
	{	
		gtk_stack_set_visible_child (stack,p3);

		PlayerName=gtk_entry_get_text(textbox);
		/*mPlayerName=gtk_entry_get_text(textbox);
		hPlayerName=gtk_entry_get_text(textbox);*/

    	gtk_label_set_text(esplayer, PlayerName);
       	gtk_label_set_text(msplayer, PlayerName);
    	gtk_label_set_text(hsplayer, PlayerName);


		//l'effet sonore
       	Mix_PlayChannel(-1, click, 0);
	}

	if (strcmp(gtk_widget_get_name(button),"e")== 0)
        {
            nbCol = 2;
            nbLigne = 3;
            nbCases = 6;
			NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p4);
			gtk_widget_show_all(infowin);
			gtk_label_set_text(scoreboard, 0);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);

        }
    if (strcmp(gtk_widget_get_name(button),"m")== 0)
        {
            nbCol = 3;
            nbLigne = 4;
            nbCases = 12;
			
			NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p5);
			gtk_widget_show_all(infowin);
			gtk_label_set_text(scoreboard, 0);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
        }
    if (strcmp(gtk_widget_get_name(button),"h")== 0)
        {
            nbCol = 4;
            nbLigne = 4;
            nbCases = 16;
            NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p6);
			gtk_label_set_text(scoreboard, 0);

			gtk_widget_show_all(infowin);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
        }

}



//Cette fonction permet de fermer le dialog qui notifi le joueur de se preparer pour commencer le jeu, lorsqu'on click "OK" le jeu commence.

void infowin_close(GtkButton *button)
{	

	//L'effet sonore
    Mix_PlayChannel(-1, click, 0);	


    if(gamemode==0)
{
	if(nbCases==6)
	{	

		
		image_flipper_front(eimg6);
		image_flipper_front(eimg5);
		image_flipper_front(eimg4);
		image_flipper_front(eimg3);
		image_flipper_front(eimg2);
		image_flipper_front(eimg1);
	
	
		gtk_widget_hide(infowin);
		labelg=label;
		start_timer();


		g_timeout_add_seconds(6, image_flipper_back, eimg6);
		g_timeout_add_seconds(6, image_flipper_back, eimg5);
		g_timeout_add_seconds(6, image_flipper_back, eimg4);
		g_timeout_add_seconds(6, image_flipper_back, eimg3);
		g_timeout_add_seconds(6, image_flipper_back, eimg2);
		g_timeout_add_seconds(6, image_flipper_back, eimg1); 
	}

	if(nbCases==12)
	{	
		image_flipper_front(mimg12);
		image_flipper_front(mimg11);
		image_flipper_front(mimg10);
		image_flipper_front(mimg9);
		image_flipper_front(mimg8);
		image_flipper_front(mimg7);
		image_flipper_front(mimg6);
		image_flipper_front(mimg5);
		image_flipper_front(mimg4);
		image_flipper_front(mimg3);
		image_flipper_front(mimg2);
		image_flipper_front(mimg1);

		gtk_widget_hide(infowin);
		labelg=label1;
		start_timer();

		g_timeout_add_seconds(6, image_flipper_back, mimg12);
		g_timeout_add_seconds(6, image_flipper_back, mimg11);
		g_timeout_add_seconds(6, image_flipper_back, mimg10);
		g_timeout_add_seconds(6, image_flipper_back, mimg9);
		g_timeout_add_seconds(6, image_flipper_back, mimg8);
		g_timeout_add_seconds(6, image_flipper_back, mimg7);
		g_timeout_add_seconds(6, image_flipper_back, mimg6);
		g_timeout_add_seconds(6, image_flipper_back, mimg5);
		g_timeout_add_seconds(6, image_flipper_back, mimg4);
		g_timeout_add_seconds(6, image_flipper_back, mimg3);
		g_timeout_add_seconds(6, image_flipper_back, mimg2);
		g_timeout_add_seconds(6, image_flipper_back, mimg1);
	}
	if(nbCases==16)
	{

		image_flipper_front(himg16);
		image_flipper_front(himg15);
		image_flipper_front(himg14);
		image_flipper_front(himg13);
		image_flipper_front(himg12);
		image_flipper_front(himg11);
		image_flipper_front(himg10);
		image_flipper_front(himg9);
		image_flipper_front(himg8);
		image_flipper_front(himg7);
		image_flipper_front(himg6);
		image_flipper_front(himg5);
		image_flipper_front(himg4);
		image_flipper_front(himg3);
		image_flipper_front(himg2);
		image_flipper_front(himg1);

		gtk_widget_hide(infowin);
		labelg=label2;
		start_timer();


		g_timeout_add_seconds(6, image_flipper_back, himg16);
		g_timeout_add_seconds(6, image_flipper_back, himg15);
		g_timeout_add_seconds(6, image_flipper_back, himg14);
		g_timeout_add_seconds(6, image_flipper_back, himg13);
		g_timeout_add_seconds(6, image_flipper_back, himg12);
		g_timeout_add_seconds(6, image_flipper_back, himg11);
		g_timeout_add_seconds(6, image_flipper_back, himg10);
		g_timeout_add_seconds(6, image_flipper_back, himg9);
		g_timeout_add_seconds(6, image_flipper_back, himg8);
		g_timeout_add_seconds(6, image_flipper_back, himg7);
		g_timeout_add_seconds(6, image_flipper_back, himg6);
		g_timeout_add_seconds(6, image_flipper_back, himg5);
		g_timeout_add_seconds(6, image_flipper_back, himg4);
		g_timeout_add_seconds(6, image_flipper_back, himg3);
		g_timeout_add_seconds(6, image_flipper_back, himg2);
		g_timeout_add_seconds(6, image_flipper_back, himg1);	
	}
}


	if(gamemode==1)
	{


	
	if(nbCases==6)
	{	

		
		image_flipper_front(meimg6);
		image_flipper_front(meimg5);
		image_flipper_front(meimg4);
		image_flipper_front(meimg3);
		image_flipper_front(meimg2);
		image_flipper_front(meimg1);
	
	
		gtk_widget_hide(infowin);
		labelg=label3;
		start_timer();


		g_timeout_add_seconds(6, image_flipper_back, meimg6);
		g_timeout_add_seconds(6, image_flipper_back, meimg5);
		g_timeout_add_seconds(6, image_flipper_back, meimg4);
		g_timeout_add_seconds(6, image_flipper_back, meimg3);
		g_timeout_add_seconds(6, image_flipper_back, meimg2);
		g_timeout_add_seconds(6, image_flipper_back, meimg1); 
	}

	if(nbCases==12)
	{	
		
		image_flipper_front(mmimg12);
		image_flipper_front(mmimg11);
		image_flipper_front(mmimg10);
		image_flipper_front(mmimg9);
		image_flipper_front(mmimg8);
		image_flipper_front(mmimg7);
		image_flipper_front(mmimg6);
		image_flipper_front(mmimg5);
		image_flipper_front(mmimg4);
		image_flipper_front(mmimg3);
		image_flipper_front(mmimg2);
		image_flipper_front(mmimg1);

		gtk_widget_hide(infowin);
		labelg=label4;
		start_timer();

		g_timeout_add_seconds(6, image_flipper_back, mmimg12);
		g_timeout_add_seconds(6, image_flipper_back, mmimg11);
		g_timeout_add_seconds(6, image_flipper_back, mmimg10);
		g_timeout_add_seconds(6, image_flipper_back, mmimg9);
		g_timeout_add_seconds(6, image_flipper_back, mmimg8);
		g_timeout_add_seconds(6, image_flipper_back, mmimg7);
		g_timeout_add_seconds(6, image_flipper_back, mmimg6);
		g_timeout_add_seconds(6, image_flipper_back, mmimg5);
		g_timeout_add_seconds(6, image_flipper_back, mmimg4);
		g_timeout_add_seconds(6, image_flipper_back, mmimg3);
		g_timeout_add_seconds(6, image_flipper_back, mmimg2);
		g_timeout_add_seconds(6, image_flipper_back, mmimg1);
	}
	if(nbCases==16)
	{

		image_flipper_front(mhimg16);
		image_flipper_front(mhimg15);
		image_flipper_front(mhimg14);
		image_flipper_front(mhimg13);
		image_flipper_front(mhimg12);
		image_flipper_front(mhimg11);
		image_flipper_front(mhimg10);
		image_flipper_front(mhimg9);
		image_flipper_front(mhimg8);
		image_flipper_front(mhimg7);
		image_flipper_front(mhimg6);
		image_flipper_front(mhimg5);
		image_flipper_front(mhimg4);
		image_flipper_front(mhimg3);
		image_flipper_front(mhimg2);
		image_flipper_front(mhimg1);

		gtk_widget_hide(infowin);
		labelg=label5;
		start_timer();


		g_timeout_add_seconds(6, image_flipper_back, mhimg16);
		g_timeout_add_seconds(6, image_flipper_back, mhimg15);
		g_timeout_add_seconds(6, image_flipper_back, mhimg14);
		g_timeout_add_seconds(6, image_flipper_back, mhimg13);
		g_timeout_add_seconds(6, image_flipper_back, mhimg12);
		g_timeout_add_seconds(6, image_flipper_back, mhimg11);
		g_timeout_add_seconds(6, image_flipper_back, mhimg10);
		g_timeout_add_seconds(6, image_flipper_back, mhimg9);
		g_timeout_add_seconds(6, image_flipper_back, mhimg8);
		g_timeout_add_seconds(6, image_flipper_back, mhimg7);
		g_timeout_add_seconds(6, image_flipper_back, mhimg6);
		g_timeout_add_seconds(6, image_flipper_back, mhimg5);
		g_timeout_add_seconds(6, image_flipper_back, mhimg4);
		g_timeout_add_seconds(6, image_flipper_back, mhimg3);
		g_timeout_add_seconds(6, image_flipper_back, mhimg2);
		g_timeout_add_seconds(6, image_flipper_back, mhimg1);	
	}
	}
}

//Cet ensemble de fonctions permet de manipuler les cartes sur la grille

void image_flipper(GtkButton *button)
{	
	
	if(nbCases==6)	
	{	
		//L'effet sonore
       	Mix_PlayChannel(-1, choose, 0);

		NameNumber = atoi(gtk_widget_get_name(button));
		GtkWidget *image=gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(image),etswiracase[NameNumber-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(image));


		//comparison des cartes:
		compare(button);	

	}


	if(nbCases==12)
	{	
		//L'effet sonore
       	Mix_PlayChannel(-1, choose, 0);

		NameNumber = atoi(gtk_widget_get_name(button));
		GtkWidget *image=gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(image),mtswiracase[NameNumber-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(image));

		compare(button);	

	}


	if(nbCases==16)
	{	
		//L'effet sonore
       	Mix_PlayChannel(-1, choose, 0);
       	
		NameNumber = atoi(gtk_widget_get_name(button));
		GtkWidget *image=gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(image),htswiracase[NameNumber-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(image));

		compare(button);	

	}

}

//Cette fonction permet de retourner une carte sur le dos

void image_flipper_back(GtkButton *button)
{	
	GtkWidget *imageback=gtk_image_new();
	gtk_image_set_from_file(GTK_IMAGE(imageback),"/home/dvss/Desktop/Memory Game/assets/V2/backc.png");
	gtk_button_set_image(button,GTK_IMAGE(imageback));
	return FALSE;
}




//Cette image permet d'afficher les cartes lorsque le countdown commence

void image_flipper_front(GtkButton *button)
{	

	if(nbCases==6)
	{
		int a = atoi(gtk_widget_get_name(button));
		GtkWidget *imageback=gtk_image_new();

		gtk_image_set_from_file(GTK_IMAGE(imageback),etswiracase[a-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(imageback));
	}


	if(nbCases==12)
	{
		int a = atoi(gtk_widget_get_name(button));
		GtkWidget *imageback=gtk_image_new();	

		gtk_image_set_from_file(GTK_IMAGE(imageback),mtswiracase[a-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(imageback));
	}


	if(nbCases==16)
	{	
		int a = atoi(gtk_widget_get_name(button));
		GtkWidget *imageback=gtk_image_new();
		gtk_image_set_from_file(GTK_IMAGE(imageback),htswiracase[a-1].ipath);
		gtk_button_set_image(button,GTK_IMAGE(imageback));
	}
}


//Cette fonction permet de comparer les cartes

void compare(GtkButton *button)
{

	
	if(compteur==0)

	{
		ListCaseCmp.NumberName1 = NameNumber;
		ListButtn[compteur]=button;
		compteur++;
		entre=false;
	}
	
	if(compteur==1 && entre == true)
	{	

		ListButtn[compteur]=button;
		ListCaseCmp.NumberName2 = NameNumber;

		if(playercurrent==1)
				{
					playercurrent=2;
				}
				else
				{
					playercurrent=1;
				}
		if(nbCases==6)
		{	
				if(etswiracase[(ListCaseCmp.NumberName1)-1].a != etswiracase[(ListCaseCmp.NumberName2)-1].a)
				{

					//l'effet sonore
       				Mix_PlayChannel(-1, wrong, 0);
		
					for(int i=0 ;i<2 ;i++)
						{
							g_timeout_add_seconds(1,image_flipper_back,ListButtn[i]);
		
						}
						
				}
				else
				{
					//l'effet sonore
       				Mix_PlayChannel(-1, success, 0);
       				score++;
       				snprintf(scorebuff, 255, "%d", score);
       				gtk_label_set_text(scoreboard, scorebuff );
       				eflipped++;

       				setscore();

       				


       				if(eflipped==3)
       				{
       					gtk_widget_show_all(scoreboard_window);

       					scoreboardG=scoreboard;

       					snprintf(fscore,255, "%s", gtk_label_get_text(scoreboardG));
       					gtk_label_set_text(finalscore, fscore);
       				}
		
				}
				
		}

		if(nbCases==12)
		{

				if(mtswiracase[(ListCaseCmp.NumberName1)-1].a != mtswiracase[(ListCaseCmp.NumberName2)-1].a)
				{
					//l'effet sonore
       				Mix_PlayChannel(-1, wrong, 0);
					for(int i=0 ;i<2 ;i++)
						{
							g_timeout_add_seconds(1,image_flipper_back,ListButtn[i]);
		
						}
				}
				else
				{
					//l'effet sonore
       				Mix_PlayChannel(-1, success, 0);
       				score++;
       				mflipped++;
       				snprintf(scorebuff, 255, "%d", score);
       				gtk_label_set_text(scoreboard1, scorebuff);

       				setscore();

       				if(mflipped==6)
       				{	
       					scoreboardG=scoreboard1;

       					snprintf(fscore,255, "%s", gtk_label_get_text(scoreboardG));
       					gtk_label_set_text(finalscore, fscore);

       					gtk_widget_show_all(scoreboard_window);
       				}
       				
				}
		}

		if(nbCases==16)
		{
				if(htswiracase[(ListCaseCmp.NumberName1)-1].a != htswiracase[(ListCaseCmp.NumberName2)-1].a)
				{
					//l'effet sonore
       				Mix_PlayChannel(-1, wrong, 0);
					for(int i=0 ;i<2 ;i++)
						{
							g_timeout_add_seconds(1,image_flipper_back,ListButtn[i]);
		
						}
				}
				else
				{
					//l'effet sonore
       				Mix_PlayChannel(-1, success, 0);
       				score++;
       				hflipped++;
       				snprintf(scorebuff, 255, "%d", score);
       				gtk_label_set_text(scoreboard2, scorebuff );

       				setscore();

       				if(hflipped==8)
       				{
       					gtk_widget_show_all(scoreboard_window);
       					scoreboardG=scoreboard2;

       					snprintf(fscore,255, "%s", gtk_label_get_text(scoreboardG));
       					gtk_label_set_text(finalscore, fscore);
       				}
				}
		}


		compteur =0;
		entre = false;
	}

	entre= true;
}


//Cette fonction sera activée lorsque le jeu est terminé. Une fenetre va s'ouvrir pour afficher le score, et une boutton pour recommencer la partie

void game_finished(GtkButton *button)

{
    if (strcmp(gtk_widget_get_name(button),"playagain")== 0 && gamemode==0)
    {
		gtk_stack_set_visible_child (stack,p3);
		pause_timer();
		reset_timer();
    	gtk_widget_hide(settings_ingame);
    //	ffscore=score;
    	score=0;
    	eflipped=0;
    	hflipped=0;
    	mflipped=0;
    	gtk_widget_hide(scoreboard_window);
		
		//l'effet sonore

       	Mix_PlayChannel(-1, click, 0);
	}
	if (strcmp(gtk_widget_get_name(button),"playagain")== 0 && gamemode==1)
    {
		gtk_stack_set_visible_child (stack,p8);
		pause_timer();
		reset_timer();
    	gtk_widget_hide(settings_ingame);
    	score=0;
    	eflipped=0;
    	hflipped=0;
    	mflipped=0;
    	gtk_widget_hide(scoreboard_window);
		
		//l'effet sonore

       	Mix_PlayChannel(-1, click, 0);
	}



    if (strcmp(gtk_widget_get_name(button),"next")== 0)
    {
    
    		gtk_stack_set_visible_child(stack, p3);
    		gtk_widget_hide(scoreboard_window);
    		eflipped=0;
    		mflipped=0;
    		hflipped=0;
    } 

}



//cettte fonction permet de choisir le mode du jeu

void game_mode(GtkButton *button)
{
	if(strcmp(gtk_widget_get_name(button),"single")==0)
	{	
		gamemode=0;
		gtk_stack_set_visible_child(stack,p2);
	}


	if(strcmp(gtk_widget_get_name(button),"multi")==0)
	{	
		gamemode=1;
		gtk_stack_set_visible_child(stack,p12);

	}

	if(strcmp(gtk_widget_get_name(button),"okm")==0)
	{	
		gtk_stack_set_visible_child(stack,p8);
		PlayerName1=gtk_entry_get_text(textbox3);
		PlayerName2=gtk_entry_get_text(textbox2);

		gtk_label_set_text(eplayer1, PlayerName1);
       	gtk_label_set_text(eplayer2, PlayerName2);

    	gtk_label_set_text(mplayer1, PlayerName1);
    	gtk_label_set_text(mplayer2, PlayerName2);

    	gtk_label_set_text(hplayer1, PlayerName1);
    	gtk_label_set_text(hplayer2, PlayerName2);

	}



}


//cette fonction permet de chosir le niveau dans le mode multijoueurs

void choose_level_multi(GtkButton *button)
{
	if (strcmp(gtk_widget_get_name(button),"me")== 0)
        {
            nbCol = 2;
            nbLigne = 3;
            nbCases = 6;
			NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p9);
			gtk_widget_show_all(infowin);
			gtk_label_set_text(scoreboard, 0);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);

        }
    if (strcmp(gtk_widget_get_name(button),"mm")== 0)
        {
            nbCol = 3;
            nbLigne = 4;
            nbCases = 12;
			
			NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p10);
			gtk_widget_show_all(infowin);
			gtk_label_set_text(scoreboard, 0);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
        }
    if (strcmp(gtk_widget_get_name(button),"mh")== 0)
        {
            nbCol = 4;
            nbLigne = 4;
            nbCases = 16;
            NombresAleatoire();
			create_struct();
			gtk_stack_set_visible_child (stack,p11);
			gtk_label_set_text(scoreboard, 0);

			gtk_widget_show_all(infowin);

			//l'effet sonore
       		Mix_PlayChannel(-1, click, 0);
        }
}


//Cette fonction permet de definir le score dans le mode multijoueurs

void setscore()
{


	if(nbCases==6)
	{
		if(gamemode==1)
		{
			if(playercurrent==1)
			{
				scorep1++;
				snprintf(scorebuff1m, 255, "%d", scorep1);
	       		gtk_label_set_text(ep1score, scorebuff1m );
	
			}
			if(playercurrent==2)
			{
				scorep2++;
				snprintf(scorebuff2m, 255, "%d", scorep2);
	       		gtk_label_set_text(ep2score, scorebuff2m );
	
			}
		}
	}

	if(nbCases==12)
	{
		if(gamemode==1)
		{
			if(playercurrent==1)
			{
				scorep1++;
				snprintf(scorebuff1m, 255, "%d", scorep1);
	       		gtk_label_set_text(mp1score, scorebuff1m );
	
			}
			if(playercurrent==2)
			{
				scorep2++;
				snprintf(scorebuff2m, 255, "%d", scorep2);
	       		gtk_label_set_text(mp2score, scorebuff2m );
	
			}
		}

	}

	if(nbCases==16)
	{
		if(gamemode==1)
		{
			if(playercurrent==1)
			{
				scorep1++;
				snprintf(scorebuff1m, 255, "%d", scorep1);
	       		gtk_label_set_text(hp1score, scorebuff1m );
	
			}
			if(playercurrent==2)
			{
				scorep2++;
				snprintf(scorebuff2m, 255, "%d", scorep2);
	       		gtk_label_set_text(hp2score, scorebuff2m );
	
			}
		}

	}
}




//Cette fonction permet de enregistrer les données des joueurs dans un fichier

void get_score(GtkWidget *button)
{
	if(strcmp(gtk_widget_get_name(button),"score")==0)
	{
		gtk_stack_set_visible_child(stack,p13);

	}

	if(whichplayer==0)
	{	
		if(gamemode==0)
		{	
			char totalbuff[250];
			int total=0;
			total+=ffscore;
	//		g_debug("%d   %d    %d", score, ffscore, total);
			snprintf(totalbuff, 255, "%d",total);
			gtk_label_set_text(player1, PlayerName);
			gtk_label_set_text(score1,  scorebuff);
			whichplayer++;
			fichier=fopen("ListeJoueurs.txt","a");
    		fprintf(fichier,"%s : %s \n",gtk_label_get_text(player1),gtk_label_get_text(score1));
        	fclose(fichier);
		}
	
/*	else
		 if(whichplayer==1)
	{	
		if(gamemode==0)
		{	
			char totalbuff[250];
			int total=0;
			total+=ffscore;
		//	g_debug("%d   %d    %d", score, ffscore, total);
			snprintf(totalbuff, 255, "%d",total);
			gtk_label_set_text(player2, PlayerName);
			gtk_label_set_text(score2,  scorebuff);
			whichplayer++;
			fichier=fopen("ListeJoueurs.txt","a");
    		fprintf(fichier,"%s : %s \n",player2,score2);
        	fclose(fichier);
		}
	}
	else if(whichplayer==2)
	{	
		if(gamemode==0)
		{	
			char totalbuff[250];
			int total=0;
			total+=ffscore;
			//g_debug("%d   %d    %d", score, ffscore, total);
			snprintf(totalbuff, 255, "%d",total);
			gtk_label_set_text(player3, PlayerName);
			gtk_label_set_text(score3,  scorebuff);
			whichplayer++;
			fichier=fopen("ListeJoueurs.txt","a");
    		fprintf(fichier,"%s : %s \n",player3,score3);
        	fclose(fichier);
		}
	}
	else	if(whichplayer==3)

	{	
		if(gamemode==0)
		{	
			char totalbuff[250];
			int total=0;
			total+=ffscore;
		//	g_debug("%d   %d    %d", score, ffscore, total);
			snprintf(totalbuff, 255, "%d",total);
			gtk_label_set_text(player5, PlayerName);
			gtk_label_set_text(score5,  scorebuff);
			whichplayer++;
			fichier=fopen("ListeJoueurs.txt","a");
    		fprintf(fichier,"%s : %s \n",player4,score4);
        	fclose(fichier);
		}

	else	if(whichplayer==4)
	
	{	
		if(gamemode==0)
		{	
			char totalbuff[250];
			int total=0;
			total+=ffscore;
		//	g_debug("%d   %d    %d", score, ffscore, total);
			snprintf(totalbuff, 255, "%d",total);
			gtk_label_set_text(player5, PlayerName);
			gtk_label_set_text(score5,  scorebuff);
			//whichplayer=0;
			fichier=fopen("ListeJoueurs.txt","a");
    		fprintf(fichier,"%s : %s \n",player5,score5);
        	fclose(fichier);
		}
	}

}
*/


}
}

//////////////
