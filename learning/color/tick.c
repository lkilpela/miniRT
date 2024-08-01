#include "/Users/lumikilpelainen/workspace/miniRT/learning/tuple.h"

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
    t_tuple new_position = add(proj.position, proj.velocity);
    t_tuple new_velocity = add(add(proj.velocity, env.gravity), env.wind);
    t_projectile new_proj = {new_position, new_velocity};
    return new_proj;
}

int main()
{
    t_tuple init_position = point(0, 1, 0);
    t_tuple init_velocity = normalize(vector(1, 1, 0));
    t_projectile p = {init_position, init_velocity};
    t_environment e = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};

    int ticks = 0;
    while (p.position.y > 0)
    {
        printf("Tick %d: Position = (%f, %f, %f)\n", ticks, p.position.x, p.position.y, p.position.z);
        p = tick(e, p);
        ticks++;
    }
    printf("Projectile hit the ground after %d ticks.\n", ticks);
}