//---------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "Particle.h"
#include "Matrix.h"

Particle::Particle()
	:	
		position(0, 0, -10),
		velocity(-3, 0, 0),
		scale(1, 1, 1),
		life(0),
		rotation(0),
		rotation_velocity(-0.25f),
		next(nullptr),
		prev(nullptr)
{
}

Particle::~Particle()
{
	// nothing to do
}

void Particle::CopyDataOnly( Particle *p )
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->position = p->position;
	this->velocity = p->velocity;
	this->scale    = p->scale;
	this->rotation = p->rotation;
	this->rotation_velocity = p->rotation_velocity;
	this->life     = p->life;
}

void Particle::Update(const float& time_elapsed)
{
	// Rotate the matrices
	Vect4D* tmp_Row0;
	tmp_Row0 = &curr_Row0;
	prev_Row0 = *tmp_Row0;

	//Vect4D tmp_Row1;
	tmp_Row0 = &curr_Row1;
	prev_Row1 = *tmp_Row0;

	//Vect4D tmp_Row2;
	tmp_Row0 = &curr_Row2;
	prev_Row2 = *tmp_Row0;

	//Vect4D tmp_Row3;
	tmp_Row0 = &curr_Row3;
	prev_Row3 = *tmp_Row0;

	Matrix tmp;

	//	Replace setters - ?
	tmp.v0 = this->diff_Row0;
	tmp.v0 = this->diff_Row1;
	tmp.v2 = this->diff_Row2;
	tmp.v3 = this->diff_Row3;
	//tmp.set(Matrix::MatrixRow::MATRIX_ROW_0, &this->diff_Row0);
	//tmp.set(Matrix::MatrixRow::MATRIX_ROW_1, &this->diff_Row1);
	//tmp.set(Matrix::MatrixRow::MATRIX_ROW_2, &this->diff_Row2);
	//tmp.set(Matrix::MatrixRow::MATRIX_ROW_3, &this->diff_Row3);

	float MatrixScale = -3*tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);
	Vect4D z_axis(0, 0, 3);
	Vect4D v(2,2,0);
	position.Cross( z_axis, v);
	v.norm(v);
	position = position + v * 0.05 * life;

	if( MatrixScale > 1 )
	{
		MatrixScale = 1/MatrixScale;
	};

	rotation = rotation + MatrixScale + rotation_velocity * time_elapsed * 2;
}

// --- End of File ---
