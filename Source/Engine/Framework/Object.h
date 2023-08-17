#pragma once
#include <string>
#include "Factory.h"
#include "Core/Json.h"

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	bool Read(const rapidjson::Value& value); \
	class Register { \
	 public: \
		Register() { \
			Factory::Instance().Register<classname>(#classname); \
	 } };

#define CLASS_DEFINITION(classname) \
		classname::Register register_class;

namespace Jackster
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); }

		virtual const char* GetClassName() {
			return "Object";
		} bool Read(const rapidjson::Value& value); class Register {
		public: Register() {
			Factory::Instance().Register<Object>("Object");
		}
		};

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string name;
	};
}