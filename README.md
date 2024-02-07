# solib_class

```c
// ~------------------------------------------------------------------------~ //
//                                                             ::: ::::::::   //
//                                                                            //
//   SOLIB                                                                    //
//                                                                            //
//   By: Zoyern <zoyern@gmail.com>                                            //
//                                                                            //
//   Created: 2024/02/04 22:53:46                                             //
//   Updated: 2024/02/04 22:53:46                                             //
//                                                                            //
// ~------------------------------------------------------------------------~ //

// ~-------------------------------------------------------------------~ //
//   SOLIB CLASSES                                        ::: ::::::::   //
//                                                                       //
//   <engine.classes.find>                                               //
//   <engine.classes.add>                                                //
//   <*(VAR*)engine.classes.get>                                         //
//   <engine.classes.remove>                                             //
// ~-------------------------------------------------------------------~ //

int main(int argc, char const *argv[])
{
	int	my_int_exemple = 42;
    double my_double_exemple = 3,14159265358979323846;
    
	// Initialisation de solib
    t_solib solib = solib_init();


	// ~---------------------------------------------------------~ //
	//   1 - Création des argument de la classe       ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //
    t_solib_construct myargs_chien[] = {
        { INT_TYPE, "ma_value", &intArg }, //creation d'un int envoie du pointeur ici *42
        { DOUBLE_TYPE, "mon_double", &doubleArg }, //creation d'un double envoie du pointeur ici *pi
        { FUNC_TYPE, "func_woaf", print_woaf }, //creation d'une fonction woaf contient toujours la class en argument et une valeur de retour
        { FUNCV_TYPE, "func_miaou", print_miaou }, //creation d'une fonction miaou contient toujours la class en argument et une valeur de retour 0 si tout vas bien > 0 si une erreur
        { VOID_TYPE, NULL, NULL }, // termine la class
    };


	// ~---------------------------------------------------------~ //
	//   2 - Ajout d'une classe dans solib            ::: ::::::   //
	//                                                             //
	//   <t_soc* add(t_solib, ClassName, t_soc_args*);>            //
	// ~---------------------------------------------------------~ //
	t_soc *my_chien_class = engine.classes.add(&solib, "CHIEN", argschien); //Ajout d'une classe dans solib (pointeur de solib, "lenom de ma classe", les agument de ma class) return le pointeur de la class 


	// ~---------------------------------------------------------~ //
	//   3 - Récuperation de la class                 ::: ::::::   //
	//                                                             //
	//   <t_soc* find(t_solib, ClassName);>                          //
	// ~---------------------------------------------------------~ //
    t_soc *my_chien_class_copy = solib.classes.find(&solib ,"CHIEN");


	// ~---------------------------------------------------------~ //
	//   4 - Obtention des valeurs                    ::: ::::::   //
	//                                                             //
	//   <void* get(t_solib, ClassName, const char*);>            //
	// ~---------------------------------------------------------~ //
    int return_mavalue = *(int*)solib.classes.get(&solib ,"CHIEN", "mavalue"); // valeur de retour = *(cast vers var*)get(solib, "class name", "var name");
    double return_mondouble = *(double*)solib.classes.get(&solib, "CHIEN", "mondouble");
    int return_woaf = *(int*)solib.classes.get(&solib, "CHIEN", "woaf");
    t_bool return_miaou = *(t_bool*)solib.classes.get(&solib, "CHIEN", "miaou");
	
	printf("mavalue : %d\n", return_mavalue); // affichera 42
    printf("mondouble : %f\n", return_mondouble); // affichera 3.14[...]
    printf("woaf : %d\n", return_woaf); // affichera 3
    printf("miaou : %d\n", return_miaou); // affichera 0

	// ~---------------------------------------------------------~ //
	//   1 - Changement dans la class                 ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //


	print_class(solib);
	my_chien_class->name = "pigeont"; // changera chien par pigeont
	int my_value = *(int*)mychienclass->getvar("mavalue"); // donnera 42
	int	my_new_value = 84;
	mychienclass->setvar("myvalue", &my_new_value);  // changera 42 par 84
	print_class(solib);
	printf("my_value (old value):%d\n", my_value); // affichera 42

    return 0;
}
```