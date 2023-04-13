#pragma once


#include <iostream>
#include <string>
#include "identity_document.h"

using namespace std::string_view_literals;

class Passport {
public:
	Passport()
	: identity_document_() {
		Passport::SetVtable(this);
		std::cout << "Passport::Ctor()"sv << std::endl;
	}
	Passport(const Passport& other)
	: identity_document_(other.identity_document_) {
		Passport::SetVtable(this);
		std::cout << "Passport::CCtor()"sv << std::endl;
	}
	~Passport() {
		std::cout << "Passport::Dtor()"sv << std::endl;
		//указатель на таблицу базового класса в деструкторе
		IdentityDocument::SetVTable((IdentityDocument*)this);
	}
			
	Passport& operator = (const Passport&) = delete;

	//оператор преобразования к базовому классу
	operator IdentityDocument() {
		return { identity_document_ };
	}

	void Delete() {
		GetVtable()->delete_this(this);
	}

	void PrintID() const {
		GetVtable()->print_id_this(this);
	}

	using DeleteFunction = void(*)(Passport*);
	using PrintIDFunction = void(*)(const Passport*);

	struct Vtable {
		DeleteFunction delete_this;
		PrintIDFunction print_id_this;
	};

	static void SetVtable(Passport* obj) {
		*(Passport::Vtable**)obj = &Passport::VTABLE;
	}

	const Vtable* GetVtable() const {
		return (const Passport::Vtable*)identity_document_.GetVtable();
	}

	Vtable* GetVtable() {
		return (Passport::Vtable*)identity_document_.GetVtable();
	}

	

private:
	//на первом месте храним экземпляр базового класса
	IdentityDocument identity_document_;
	static Passport::Vtable VTABLE; //сама таблица
	

	static void Delete(Passport* obj) {
		delete obj;
	}

	static void PrintID(const Passport*) {
		std::cout << "Passport::PrintID() : "sv << std::endl;
	}
};

Passport::Vtable Passport::VTABLE = {
	Passport::Delete, Passport::PrintID
};
 
