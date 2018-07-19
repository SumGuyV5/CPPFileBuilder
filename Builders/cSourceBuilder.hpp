#ifndef _CSOURCEBUILDER_HPP_
#define _CSOURCEBUILDER_HPP_

#include "cBaseBuilder.hpp"

#include <string>

namespace Builders {
	class cSourceBuilder : public cBaseBuilder
	{
	public:
		cSourceBuilder(const std::string& class_name, const std::string& name_space, const bool singleton = false);	// default constructor
		~cSourceBuilder();

		void Build();

	private:
		void PreprocessorBuild();
		void NameSpaceBuild();
		void VariableBuild();
		void ConstructorBuild();
		void FunctionsBuild();
		
		void SingletonBuild();

		void GettersBuild();
		void SettersBuild();

		const std::string StringBuild(const Model::cVariableModel* var, eStringType type) const;
	};/// END CLASS DEFINITION cSourceBuilder
}/// END NAMESPACE DEFINITION Build
#endif/// END IFNDEF _CSOURCEBUILDER_HPP_
