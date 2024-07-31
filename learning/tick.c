#include "tuple.h"

typedef struct s_projectile
{
    t_tuple position;
    t_tuple velocity;
}              t_projectile;

typedef struct s_environment
{
    t_tuple gravity;
    t_tuple wind;
}               t_environment;

t_projectile tick(t_environment env, t_projectile proj)
{
    
}