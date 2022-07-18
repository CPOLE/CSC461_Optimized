//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	
	~Particle();
	void Update(const float& time_elapsed);
	void CopyDataOnly( Particle *p );

private:
	Vect4D	prev_Row0;
	Vect4D	prev_Row1;
	Vect4D  prev_Row2;
	Vect4D  prev_Row3;

	Vect4D  diff_Row0;
	Vect4D  diff_Row1;
	Vect4D  diff_Row2;
	Vect4D  diff_Row3;

	Vect4D  curr_Row0;
	Vect4D	curr_Row1;
	Vect4D  curr_Row2;
	Vect4D  curr_Row3;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;

	float	life;
	float	rotation;
	float	rotation_velocity;

	Particle *next;
	Particle *prev;







};

#endif 

// --- End of File ---
