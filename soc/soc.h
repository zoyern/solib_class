/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:45:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/07 16:47:53 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOC_H
# define SOC_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0
typedef int t_bool;


//regles !!
// so_solib big struct
// so_		game struct
// so_class big class struct
// soc_		class struct
// soc_		class struct
// soc_e		class struct enum
// soc_e_name		class struct enum classname
// soc_e_args		class struct enum args
// soc_e_var		class struct enum var type

typedef struct s_solib t_solib;
typedef struct s_soc t_soc;

typedef enum {
	NULL_TYPE,
	CHAR_TYPE,
	SIGNED_CHAR_TYPE,
	UNSIGNED_CHAR_TYPE,
	SHORT_TYPE,
	SHORT_INT_TYPE,
	SIGNED_SHORT_TYPE,
	SIGNED_SHORT_INT_TYPE,
	UNSIGNED_SHORT_TYPE,
	UNSIGNED_SHORT_INT_TYPE,
	SIGNED_TYPE,
	SIGNED_INT_TYPE,
	UNSIGNED_TYPE,
	UNSIGNED_INT_TYPE,
	LONG_TYPE,
	LONG_INT_TYPE,
	SIGNED_LONG_TYPE,
	SIGNED_LONG_INT_TYPE,
	UNSIGNED_LONG_TYPE,
	UNSIGNED_LONG_INT_TYPE,
	LONG_LONG_TYPE,
	LONG_LONG_INT_TYPE,
	SIGNED_LONG_LONG_TYPE,
	SIGNED_LONG_LONG_INT_TYPE,
	UNSIGNED_LONG_LONG_TYPE,
	UNSIGNED_LONG_LONG_INT_TYPE,
	INT_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	LONG_DOUBLE_TYPE,
	STRING_TYPE,
	BOOL_TYPE,
	POINTER_TYPE,
	ENUM_TYPE,
	FUNC_TYPE,
	FUNCV_TYPE,
	FUNC_ARGS_TYPE,
} t_soc_type;

// Structure représentant un argument : 
// { TYPE, "mavalue", &intArg },
typedef struct s_soc_args{
    t_soc_type type;
    const char *name;
    void* value;
} t_soc_args;

// Structure représentant une classe dynamique

typedef struct s_soc{
	t_bool		isNull;
	const char * name; 
    t_soc_args* args;
	int			args_size;
	void* (*setvar)(t_soc *so_class, const char* varname, t_soc_type type, void *value);
	void* (*getvar)(t_soc *so_class, const char* varname);
	void *so_return;
} t_soc;

// Structure représentant les classes dynamiques
typedef struct s_so_classes{
    t_soc class[10];
    t_soc* (*find)(t_solib *solib, const char *soc_name);
    void* (*get)(t_solib *solib, const char *soc_name, const char* propName);
    void* (*remove)(t_solib *solib, const char *soc_name, const char* propName);
    t_soc *(*construct)(t_solib *solib, const char *soc_name, ...);
} t_so_classes;

// Structure représentant solib
typedef struct s_solib{
    t_so_classes classes;
} t_solib;

t_solib solib_init();
t_so_classes	so_solib_classes_init();
void			*so_get_class_value(t_solib *solib, const char *soc_name, const char* varname);
void			*so_class_getvar(t_soc *so_class, const char* varname);
void			*so_class_setvar(t_soc *so_class, const char* varname, t_soc_type type, void *value);
t_soc			*so_add_class(t_solib *solib, const char *soc_name, t_soc_args* args);
t_soc			*so_find_class(t_solib *solib, const char *soc_name);
void			so_print_classes(t_solib solib);
t_soc			*so_class_constructor(t_solib *solib, const char *soc_name, ...);

int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif