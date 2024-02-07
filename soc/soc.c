/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:02:10 by marvin            #+#    #+#             */
/*   Updated: 2024/02/07 16:51:21 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soc.h"

void so_print_classes(t_solib solib)
{
	for (int i = 0; !solib.classes.class[i].isNull; ++i) {
        printf("\n--------------------------------\n---name :%s\n", solib.classes.class[i].name);
		printf("args |name: args_size  -- value :%d\n", solib.classes.class[i].args_size);
        printf("pointer :%p\n", &solib.classes.class[i]);
		for (int j = 0; j < solib.classes.class[i].args_size; ++j) {
        	printf("args |name: %s  -- value :%u\n", solib.classes.class[i].args[j].name, solib.classes.class[i].args[j].type);
    	}
    }
	printf("--------------------------------\n\n\n\n");
}

t_soc *so_find_class(t_solib *solib, const char *soc_name) {
	int	i;

	i = 0;
	while (!solib->classes.class[i].isNull)
	{
		if (ft_strcmp(solib->classes.class[i].name, soc_name) == 0) {
			return (&solib->classes.class[i]);
		}
		i++;
	}
	printf("classes.find Unfind:\n\n==>|<%s?>|-><?> !\n\n", solib->classes.class[i].name);
	return (NULL);
}

void	*so_class_getvar(t_soc *so_class, const char* varname)
{
	int	i;

	i = 0;
	while (i < so_class->args_size)
	{
		if (ft_strcmp(so_class->args[i].name, varname) == 0)
		{
			if (so_class->args[i].type == FUNC_TYPE) {
				void (*fun_ptr)(t_soc *) = so_class->args[i].value;
				(*fun_ptr)(so_class);
				return (so_class->so_return);
			}
			else
				return (so_class->args[i].value);
		}
		i++;
	}
	printf("getvar Unfind:\n\n==><%s>->|<%s?>| !\n\n", so_class->name, varname);
	return (NULL); //non trouvé
}

void	*so_class_setvar(t_soc *so_class, const char* varname, t_soc_type type, void *value)
{
	int	i;

	i = 0;
	while (i < so_class->args_size)
	{
		if (ft_strcmp(so_class->args[i].name, varname) == 0)
		{
			so_class->args[i].value = value;
			so_class->args[i].type = type;
			return (so_class->args[i].value);
		}
		i++;
	}
	return (NULL); //non trouvé
}

// Fonction pour ajouter une classe
t_soc *so_add_class(t_solib *solib, const char *soc_name, t_soc_args* args) {
    // Recherche de la première classe libre dans le tableau
    int i;
	int	j;

	i = 0;
	j = 0;
    while (i < 10) {
        if (solib->classes.class[i].isNull)
            break;
		i++;
    }
	if (i == 10)
		return (NULL);
	while (j < 5) {
		printf("%s -- %u -- %d\n", args[j].name, args[j].type, j);
        j++;
    }
	printf("j --- %d\n", j);

    // Initialisation de la nouvelle classe
    t_soc newClass;
    newClass.name = soc_name;
    newClass.isNull = FALSE;
    newClass.args_size = j;
	newClass.args = args;
	newClass.getvar = so_class_getvar;
	newClass.setvar = so_class_setvar;
    // Affecter la nouvelle classe au moteur
    solib->classes.class[i] = newClass;
	return (&solib->classes.class[i]);
}


t_soc *so_class_constructor(t_solib *solib, const char *soc_name, ...) {
	(void)solib;
	va_list ap;
    int i;
	t_soc_type type;
	char *name;
	void *value;
    va_start(ap, soc_name);
	type = va_arg(ap, t_soc_type);
	name = va_arg(ap, char *);
	value = va_arg(ap, void *);
    for(i=0; type != NULL_TYPE  ;i++){
    	printf("-------------%u -- %s -- %p\n", type, name, value);
		
		type = va_arg(ap, t_soc_type);
		name = va_arg(ap, char *);
		value = va_arg(ap, void *);
    }
    va_end(ap);
	t_soc *tted;
	tted = malloc(sizeof(t_soc *));
    return (tted);
}


// Fonction pour obtenir une valeur à partir de la classe dynamique par nom de class et nom de la variable


void	*so_get_class_value(t_solib *solib, const char *soc_name, const char* varname)
{
	t_soc	*tmp_class;
	void	*result;

	result = NULL;
	tmp_class = so_find_class(solib, soc_name);
	if (!tmp_class)
		return (result);
	result = so_class_getvar(tmp_class, varname);
	return (result);
}

// Fonction pour initialiser les classes
t_so_classes so_solib_classes_init() {
    t_so_classes classes;
	for (int i = 0; i < 10; i++)
	{
		classes.class[i].isNull = TRUE;
		classes.class[i].args_size = 0;
	}
    classes.find = so_find_class;
    classes.construct = so_class_constructor;
    classes.get = so_get_class_value;
    return classes;
}

// Fonction pour initialiser le moteur
t_solib solib_init() {
    t_solib solib;
    solib.classes = so_solib_classes_init();

	for (int i = 0; i < 10; ++i) {
        solib.classes.class[i].args = NULL;
    }
    return solib;
}

/*int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	int	my_int_exemple = 42;
    double my_double_exemple = 3.14159265358979323846;
    
	// Initialisation de solib
    t_solib solib = solib_init();


	// ~---------------------------------------------------------~ //
	//   1 - Création des argument de la classe       ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //
    t_soc_args my_args_chien[] = {
        { INT_TYPE, "ma_value", &my_int_exemple }, //creation d'un int envoie du pointeur ici *42
        { DOUBLE_TYPE, "mon_double", &my_double_exemple }, //creation d'un double envoie du pointeur ici *pi
        { FUNC_TYPE, "func_woaf", print_woaf }, //creation d'une fonction woaf contient toujours la class en argument et une valeur de retour
        { FUNC_TYPE, "func_miaou", print_miaou }, //creation d'une fonction miaou contient toujours la class en argument et une valeur de retour 0 si tout vas bien > 0 si une erreur
    };


	// ~---------------------------------------------------------~ //
	//   2 - Ajout d'une classe dans solib            ::: ::::::   //
	//                                                             //
	//   <t_soc* add(t_solib, ClassName, t_soc_args*);>            //
	// ~---------------------------------------------------------~ //
	t_soc *my_chien_class = solib.classes.add(&solib, "CHIEN", my_args_chien); //Ajout d'une classe dans solib (pointeur de solib, "lenom de ma classe", les agument de ma class) return le pointeur de la class 


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
    int return_woaf = *(int*)solib.classes.get(&solib, "CHIEN", "func_woaf");
    t_bool return_miaou = *(t_bool*)solib.classes.get(&solib, "CHIEN", "func_miaou");
	
	printf("mavalue : %d\n", return_mavalue); // affichera 42
    printf("mondouble : %f\n", return_mondouble); // affichera 3.14[...]
    printf("woaf : %d\n", return_woaf); // affichera 3
    printf("miaou : %d\n", return_miaou); // affichera 0

	// ~---------------------------------------------------------~ //
	//   1 - Changement dans la class                 ::: ::::::   //
	//                                                             //
	//   <t_solib_construct myargs_chien[];>                       //
	// ~---------------------------------------------------------~ //


	so_print_class(solib);
	my_chien_class->name = "pigeon"; // changera chien par pigeont
	//int my_value = *(int*)my_chien_class->getvar("mavalue"); // donnera 42
	//int	my_new_value = 84;
	//mychienclass->setvar("myvalue", &my_new_value);  // changera 42 par 84
	so_print_class(solib);
	my_chien_class_copy->name = "chat";
	so_print_class(solib);
	t_soc newclassadd = *my_chien_class;
	my_chien_class_copy->name = "CHIEN";
	solib.classes.add(&solib, newclassadd.name, newclassadd.args);
	so_print_class(solib);

    return 0;
}*/