
#include <SDL.h>
#include <ScriptingSDK.h>
#include "ModuleSDK.h"

using namespace Galactic3D;

static ModuleAPI* g_pAPI;

extern void* SDLCALL MyRegisterModule(ReflectedNamespace* pNamespace);
extern void SDLCALL MyUnregisterModule(void* pUser);

extern "C" __declspec(dllexport) void* SDLCALL RegisterModule(ReflectedNamespace* pNamespace, Galactic3D::ModuleAPI* pAPI)
{
	g_pAPI = pAPI;

	return MyRegisterModule(pNamespace);
}

extern "C" __declspec(dllexport) void SDLCALL UnregisterModule(void* pUser)
{
	MyUnregisterModule(pUser);
}

// Referenceable

void Referenceable::SetPrivate(void* pPrivate)
{
	return g_pAPI->SetPrivate(this, pPrivate);
}

void* Referenceable::GetPrivate()
{
	return g_pAPI->GetPrivate(this);
}

// ReflectedClass

ReflectedProperty* ReflectedClass::GetProperty(const char* pszName)
{
	return g_pAPI->LookupClassProperty(this, pszName);
}

ReflectedFunction* ReflectedClass::GetFunction(const char* pszName)
{
	return g_pAPI->LookupClassFunction(this, pszName);
}

bool ReflectedClass::RegisterConstructor(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterClassConstructor(this, pFunction, pUser);
}

bool ReflectedClass::RegisterClone(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterClassClone(this, pFunction, pUser);
}

bool ReflectedClass::RegisterMove(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterClassMove(this, pFunction, pUser);
}

bool ReflectedClass::RegisterToString(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterClassToString(this, pFunction, pUser);
}

bool ReflectedClass::RegisterFunction(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterClassFunction(this, pFunction, pUser);
}

bool ReflectedClass::AddProperty(void* pUser, const char* pszName, unsigned char Type, const ScriptFunction* pGetter, const ScriptFunction* pSetter)
{
	return g_pAPI->AddClassProperty(this, pUser, pszName, Type, pGetter, pSetter);
}

// ReflectedNamespace

ReflectedProperty* ReflectedNamespace::GetProperty(const char* pszName)
{
	return g_pAPI->LookupNamespaceProperty(this, pszName);
}

ReflectedFunction* ReflectedNamespace::GetFunction(const char* pszName)
{
	return g_pAPI->LookupNamespaceFunction(this, pszName);
}

bool ReflectedNamespace::RegisterFunction(const ScriptFunction* pFunction, void* pUser)
{
	return g_pAPI->RegisterNamespaceFunction(this, pFunction, pUser);
}

bool ReflectedNamespace::AddProperty(void* pUser, const char* pszName, unsigned char Type, const ScriptFunction* pGetter, const ScriptFunction* pSetter)
{
	return g_pAPI->AddNamespaceProperty(this, pUser, pszName, Type, pGetter, pSetter);
}

ReflectedClass* ReflectedNamespace::NewClass(ReflectedClassDecl* pClassDecl, ReflectedClass* pParent)
{
	return g_pAPI->NewClass(this, pClassDecl, pParent);
}

// Argument

unsigned char CArgument::GetType(void) const
{
	return g_pAPI->Argument_GetType(this);
}

const char* CArgument::GetTypeName(void) const
{
	return g_pAPI->Argument_GetTypeName(this);
}

bool CArgument::IsNull(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_NIL || Type == ARGUMENT_UNDEFINED)
		return true;
	return false;
}

bool CArgument::IsBoolean(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_BOOLEAN)
		return true;
	return false;
}

bool CArgument::IsString(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_STRING)
		return true;
	return false;
}

bool CArgument::IsReferenceable(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_REFERENCEABLE)
		return true;
	return false;
}

bool CArgument::IsVector2D(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_VECTOR2D)
		return true;
	return false;
}

bool CArgument::IsVector3D(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_VECTOR3D)
		return true;
	return false;
}

bool CArgument::IsVector4D(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_VECTOR4D)
		return true;
	return false;
}

bool CArgument::IsMatrix4x4(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_MATRIX4X4)
		return true;
	return false;
}

bool CArgument::IsNumber(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_INTEGER)
		return true;
	else if (Type == ARGUMENT_LONGINTEGER)
		return true;
	else if (Type == ARGUMENT_FLOAT)
		return true;
	else if (Type == ARGUMENT_DOUBLE)
		return true;
	return false;
}

bool CArgument::IsArray(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_ARRAY)
		return true;
	return false;
}

bool CArgument::IsFunction(void) const
{
	unsigned char Type = GetType();
	if (Type == ARGUMENT_FUNCTION)
		return true;
	return false;
}

bool CArgument::ToBoolean(void) const
{
	return g_pAPI->Argument_ToBoolean(this);
}

const char* CArgument::ToString(size_t* pLength) const
{
	return g_pAPI->Argument_ToString(this, pLength);
}

Referenceable* CArgument::ToReferenceable(ReflectedClass* pClass) const
{
	return g_pAPI->Argument_ToReferenceableClass(this, pClass);
}

Referenceable* CArgument::ToReferenceable(void) const
{
	return g_pAPI->Argument_ToReferenceable(this);
}

void CArgument::ToVector2D(Math::Vector2D& vec) const
{
	return g_pAPI->Argument_ToVector2D(this, vec);
}

void CArgument::ToVector3D(Math::Vector3D& vec) const
{
	return g_pAPI->Argument_ToVector3D(this, vec);
}

void CArgument::ToVector4D(Math::Vector4D& vec) const
{
	return g_pAPI->Argument_ToVector4D(this, vec);
}

void CArgument::ToMatrix4x4(Math::Matrix4x4& mat) const
{
	return g_pAPI->Argument_ToMatrix4x4(this, mat);
}

// Reflection

const char* Reflection::GetLastError(void)
{
	return g_pAPI->GetLastError();
}

Referenceable* Reflection::Clone(Referenceable* pReferenceable)
{
	return g_pAPI->Clone(pReferenceable);
}

bool Reflection::Move(Referenceable* pReferenceable, Referenceable* pNewReferenceable)
{
	return g_pAPI->Move(pReferenceable, pNewReferenceable);
}

char* Reflection::ToString(Referenceable* pReferenceable, size_t* pLength)
{
	return g_pAPI->ToString(pReferenceable, pLength);
}

ReflectedProperty* Reflection::LookupProperty(Referenceable* pReferenceable, const char* pszName)
{
	return g_pAPI->LookupProperty(pReferenceable, pszName);
}

ReflectedFunction* Reflection::LookupFunction(Referenceable* pReferenceable, const char* pszName)
{
	return g_pAPI->LookupFunction(pReferenceable, pszName);
}

bool Reflection::GetProperty(Referenceable* pReferenceable, ReflectedProperty* pProperty, CReturnValue* pReturnValue)
{
	return g_pAPI->GetPropertyPtr(pReferenceable, pProperty, pReturnValue);
}

bool Reflection::GetProperty(Referenceable* pReferenceable, const char* pszName, CReturnValue* pReturnValue)
{
	return g_pAPI->GetPropertyStr(pReferenceable, pszName, pReturnValue);
}

bool Reflection::SetProperty(Referenceable* pReferenceable, ReflectedProperty* pProperty, CArguments* pArguments)
{
	return g_pAPI->SetPropertyPtr(pReferenceable, pProperty, pArguments);
}

bool Reflection::SetProperty(Referenceable* pReferenceable, const char* pszName, CArguments* pArguments)
{
	return g_pAPI->SetPropertyStr(pReferenceable, pszName, pArguments);
}

bool Reflection::Call(Referenceable* pThis, ReflectedFunction* pFunction, CArguments* pArguments, CReturnValue* pReturnValue)
{
	return g_pAPI->Call(pThis, pFunction, pArguments, pReturnValue);
}

bool Reflection::Call(Referenceable* pThis, const char* pszName, CArguments* pArguments, CReturnValue* pReturnValue)
{
	return g_pAPI->CallMemb(pThis, pszName, pArguments, pReturnValue);
}

Referenceable* Reflection::New(ReferenceableFinaliser Finaliser, ReflectedClass* pClass)
{
	return g_pAPI->New(Finaliser, pClass);
}

// SDL

extern SDL_AssertState SDLCALL SDL_ReportAssertion(SDL_AssertData *,
	const char *,
	const char *, int)
{
	return SDL_ASSERTION_IGNORE;
}

extern void *SDLCALL SDL_malloc(size_t size)
{
	return g_pAPI->Alloc(size);
}

// TODO: Export this
extern void *SDLCALL SDL_calloc(size_t nmemb, size_t size)
{
	void* pMemory = SDL_malloc(nmemb*size);
	memset(pMemory, 0, nmemb*size);
	return pMemory;
}

extern void *SDLCALL SDL_realloc(void *mem, size_t size)
{
	return g_pAPI->ReAlloc(mem, size);
}

extern void SDLCALL SDL_free(void *mem)
{
	g_pAPI->Free(mem);
}

const char *SDLCALL SDL_GetError(void)
{
	return g_pAPI->GetLastError();
}
