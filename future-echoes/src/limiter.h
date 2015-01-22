/*
 *  limiter.h
 *  memoryMosaicIPhone
 *
 *  Created by Mr. Magoo on 10/28/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include <math.h>

using namespace std;

class EnvelopeFollower 
{ 
public: 
	EnvelopeFollower(); 
	
	void Setup( float attackMs, float releaseMs, int sampleRate ); 
	
	template<class T, int skip> 
	void Process( size_t count, const T *src ); 
	
	float envelope; 
	
protected: 
	float a; 
	float r; 
}; 

//----------------------- 

class Clipper 
{ 
public: 
	Clipper(); 
	
	template<class T, int skip> 
	void Process( size_t count, T *dest ); 
	
	bool bClipped; 
}; 

//----------------------- 

struct Limiter 
{ 
	void Setup( float attackMs, float releaseMs, int sampleRate ); 
	
	template<class T, int skip> 
	void Process( size_t nSamples, T *dest ); 
	EnvelopeFollower e; 
}; 

//----------------------- 

inline EnvelopeFollower::EnvelopeFollower() 
{ 
	envelope=0; 
} 

inline void EnvelopeFollower::Setup( float attackMs, float releaseMs, int sampleRate ) 
{ 
	a = powf( 0.01, 1.0 / ( attackMs * sampleRate * 0.001 ) ); 
	r = powf( 0.01, 1.0 / ( releaseMs * sampleRate * 0.001 ) ); 
} 

template<class T, int skip> 
void EnvelopeFollower::Process( size_t count, const T *src ) 
{ 
	while( count-- ) 
	{ 
		float v=::fabs( *src ); 
		src+=skip; 
		if( v>envelope ) 
			envelope = a * ( envelope - v ) + v; 
		else 
			envelope = r * ( envelope - v ) + v; 
	} 
} 

//----------------------- 

inline Clipper::Clipper() 
{ 
	bClipped=false; 
} 

template<class T, int skip> 
void Clipper::Process( size_t count, T *dest ) 
{ 
	bClipped=false; 
	while( count-- ) 
	{ 
		if( *dest>1 ) 
		{ 
			*dest=1; 
			bClipped=true; 
		} 
		else if( *dest<-1 ) 
		{ 
			*dest=-1; 
			bClipped=true; 
		} 
		dest+=skip; 
	} 
} 

//----------------------- 

inline void Limiter::Setup( float attackMs, float releaseMs, int sampleRate ) 
{ 
	e.Setup( attackMs, releaseMs, sampleRate ); 
} 

template<class T, int skip> 
void Limiter::Process( size_t count, T *dest ) 
{ 
	while( count-- ) 
	{ 
		T v=*dest; 
		// don't worry, this should get optimized 
		e.Process<T, skip>( 1, &v ); 
		if( e.envelope>1.0f ) 
			*dest=*dest/e.envelope; 
		dest+=skip; 
	} 
} 