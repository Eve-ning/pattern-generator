#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#include "includes.h"

namespace manialib_compiler {

	class Compiler {

	public:

		//Compiles parameters into single notes
		//Input (Int) Number of Keys, (Int) Key of note, (Double) Offset, (Optional String) Extension
		//Return NIL
		void Compiler_NN(int, int, double, std::string = "1,0,0:0:0:0:");

		//Compiles parameters into long notes
		//Input (Int) Number of Keys, (Int) Key of note, (Double) Start Offset, (Double) End Offset, (Optional String) Extension
		//Return NIL
		void Compiler_NL(int, int, double, double, std::string = ":0:0:0:0:");

		//Compiles parameters into a Timing Point
		//Input (Double) Offset, (Double) Code, (Bool) SV or BPM, (Optional String) Extension
		//Return NIL
		void Compiler_T(double, double, bool, std::string = "DEFAULT");

	};

}
#endif // !COMPILER_H
