/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soc_exemple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:03:27 by marvin            #+#    #+#             */
/*   Updated: 2024/02/07 17:34:13 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soc/soc.h"
#include <stdarg.h>

void print_woaf(t_soc *so_this) {
	
    printf("woaf!\n");
	int returnvalue = 3;

	so_this->so_return = &returnvalue;
}

void print_miaou(t_soc *so_this) {
	/*float damage;

	damage = 20/100* (*(float*)(so_this->getvar(so_this, "my_health_exemple")));
	printf("miaou!\n");
	so_this->setvar(so_this, "my_health_exemple", &damage);*/
	t_bool returnvalue = FALSE;

	so_this->so_return = &returnvalue;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
    
	// Initialisation de solib
    t_solib solib = solib_init();

	int	my_int_exemple = 42;
    double my_double_exemple = 3.14159265358979323846;
    float my_health_exemple = 200.0f;
	// ~---------------------------------------------------------~ //
	//   1 - Création des argument de la classe       ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //
	t_soc *my_chien_class = solib.classes.construct(&solib, "CHIEN",
		INT_TYPE, "ma_value", &my_int_exemple, //creation d'un int envoie du pointeur ici *42
        DOUBLE_TYPE, "mon_double", &my_double_exemple,//creation d'un double envoie du pointeur ici *pi
        FLOAT_TYPE, "my_health_exemple", &my_health_exemple,
        FUNC_TYPE, "func_woaf", print_woaf,//creation d'une fonction woaf contient toujours la class en argument et une valeur de retour
        FUNC_TYPE, "func_miaou", print_miaou, //creation d'une fonction miaou contient toujours la class en argument et une valeur de retour 0 si tout vas bien > 0 si une erreur
		NULL_TYPE);


	// ~---------------------------------------------------------~ //
	//   2 - Ajout d'une classe dans solib            ::: ::::::   //
	//                                                             //
	//   <t_soc* add(t_solib, ClassName, t_soc_args*);>            //
	// ~---------------------------------------------------------~ //
	//t_soc *my_chien_class = solib.classes.add(&solib, "CHIEN", my_args_chien); //Ajout d'une classe dans solib (pointeur de solib, "lenom de ma classe", les agument de ma class) return le pointeur de la class 


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
    int return_mavalue = *(int*)solib.classes.get(&solib ,"CHIEN", "ma_value"); // valeur de retour = *(cast vers var*)get(solib, "class name", "var name");
    double return_mondouble = *(double*)solib.classes.get(&solib, "CHIEN", "mon_double");
    float return_heath = *(float*)solib.classes.get(&solib, "CHIEN", "my_health_exemple");
    int return_woaf = *(int*)solib.classes.get(&solib, "CHIEN", "func_woaf");
    t_bool return_miaou = *(t_bool*)solib.classes.get(&solib, "CHIEN", "func_miaou");
	
	printf("args : %d\n", my_chien_class->args_size); // affichera
	printf("mavalue : %d\n", return_mavalue); // affichera 42
    printf("mondouble : %f\n", return_mondouble); // affichera 3.14[...]
    printf("return_heath : %f\n", return_heath); // affichera 3.14[...]
    printf("woaf : %d\n", return_woaf); // affichera 3
    printf("miaou : %d\n", return_miaou); // affichera 0

	// ~---------------------------------------------------------~ //
	//   1 - Changement dans la class                 ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //


	so_print_classes(solib);
	my_chien_class->name = "pigeon"; // changera chien par pigeont
	int my_value = *(int*)my_chien_class->getvar(my_chien_class, "mavalue"); // donnera 42
	(void)my_value;
	int	my_new_value = 84;
	my_chien_class->setvar(my_chien_class, "myvalue", INT_TYPE, &my_new_value);  // changera 42 par 84
	so_print_classes(solib);
	my_chien_class_copy->name = "chat";
	so_print_classes(solib);
	t_soc newclassadd = *my_chien_class;
	my_chien_class_copy->name = "CHIEN";
	char *my_new_string = "500";
	my_chien_class_copy->setvar(my_chien_class_copy, "my_health_exemple", STRING_TYPE, &my_new_string);
	solib.classes.construct(&solib, newclassadd.name, newclassadd.args);
	so_print_classes(solib);

    return 0;
}