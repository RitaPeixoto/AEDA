#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ClubeVideo.h"
#include <math.h>


using testing::Eq;
using namespace std;



TEST(test_1,test_a) {
	/**
	ClubeVideo vc;

	Cliente c1("Joao");
	Cliente c2("Maria");
	Cliente c3("Ana");
	Cliente c4("Pedro");

	vc.addCliente(c1);
	vc.addCliente(c2);
	vc.addCliente(c3);
	vc.addCliente(c4);

	EXPECT_EQ(true, vc.existeCliente("Pedro"));
	EXPECT_EQ(true, vc.existeCliente("Maria"));
	EXPECT_EQ(false, vc.existeCliente("Carlos"));
	EXPECT_EQ(false, vc.existeCliente("Andre"));

	Filme dvd1("Alcatraz");
	Filme dvd2("Al Capone");
	Filme dvd3("Big Bang Theory, The");
	Filme dvd4("Big Fish");
	Filme dvd5("Doctor Who");
	Filme dvd6("Man of Steel");
	Filme dvd7("Red Tails");
	Filme dvd8("Harry Potter");

	vc.addFilme(dvd1);
	vc.addFilme(dvd2);
	vc.addFilme(dvd3);
	vc.addFilme(dvd4);
	vc.addFilme(dvd5);
	vc.addFilme(dvd6);
	vc.addFilme(dvd7);
	vc.addFilme(dvd8);

	EXPECT_EQ(true, vc.existeFilme("Big Bang Theory, The"));
	EXPECT_EQ(true, vc.existeFilme("Red Tails"));
	EXPECT_EQ(true, vc.existeFilme("Doctor Who"));
	EXPECT_EQ(false, vc.existeFilme("True Lies"));
	EXPECT_EQ(false, vc.existeFilme("Spider-Man"));

	Cliente c5("Simao");   c5.addFilme( Filme("True Lies") );
	Cliente c6("Eduardo"); c6.addFilme( Filme("Spider-Man") );
	vc.addCliente(c5);
	vc.addCliente(c6);

	EXPECT_EQ(true, vc.existeFilme("True Lies"));
	EXPECT_EQ(true, vc.existeFilme("Spider-Man"));
	*/
}

TEST(test_1,test_b) {
	/**
	ClubeVideo vc1;

	vc1.addFilme( Filme("Harry Potter") );
	vc1.addFilme( Filme("Gladiator") );
	vc1.addFilme( Filme("Batman") );

	EXPECT_EQ("Harry Potter 0\nGladiator 0\nBatman 0\n", vc1.imprimirFilmes());

	ClubeVideo vc2;
	EXPECT_EQ("", vc2.imprimirFilmes());

	ClubeVideo vc3;
	Cliente c1("Antonio");
	Cliente c2("Elisabete");

	c1.addFilme( Filme("Dune") );
	c2.addFilme( Filme("Top Gun") );
	c2.addFilme( Filme("Godfather, The") );

	vc3.addCliente(c1);
	vc3.addCliente(c2);

	EXPECT_EQ("Dune 0\nGodfather, The 0\nTop Gun 0\n", vc3.imprimirFilmes());
	*/
}

TEST(test_1,test_c) {
	/**
	ClubeVideo vc;
	list<string> ls = vc.titulosDisponiveis();

	EXPECT_EQ(0, ls.size());

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Gladiator") );
	vc.addFilme( Filme("Batman") );

	ls = vc.titulosDisponiveis();
	EXPECT_EQ(3, ls.size());

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Mozart") );

	ls = vc.titulosDisponiveis();
	EXPECT_EQ(4, ls.size());

	Cliente c("Pedro");
	c.addFilme( Filme("Gladiator") );
	c.addFilme( Filme("Internship, The") );
	vc.addCliente(c);

	ls = vc.titulosDisponiveis();
	EXPECT_EQ(4, ls.size());

	stringstream ss;
	for(list<string>::iterator itl = ls.begin(); itl != ls.end(); ++itl) {
		ss << (*itl) << "\n";
	}

	EXPECT_EQ("Batman\nGladiator\nHarry Potter\nMozart\n", ss.str());
	*/
}

TEST(test_1,test_d) {
	/**
	ClubeVideo vc;

	vc.addFilme( Filme("Harry Potter") );
	vc.addFilme( Filme("Gladiator") );
	vc.addFilme( Filme("Batman") );

	EXPECT_EQ(true, vc.tituloDisponivel("Gladiator"));
	EXPECT_EQ(true, vc.tituloDisponivel("Harry Potter"));
	EXPECT_EQ(false, vc.tituloDisponivel("Platoon"));

	vc.addFilme( Filme("Platoon") );
	EXPECT_EQ(true, vc.tituloDisponivel("Batman"));
	EXPECT_EQ(true, vc.tituloDisponivel("Platoon"));

	Cliente c1("Joao");
	c1.addFilme( Filme("We Were Soldiers") );
	vc.addCliente(c1);

	EXPECT_EQ(false, vc.tituloDisponivel("We Were Soldiers"));
	*/
}

TEST(test_1,test_e){
	/**
	ClubeVideo vc;

	vc.addPedidoCliente(PedidoCliente("Joao", "Gladiator"));
	vc.addPedidoCliente(PedidoCliente("Maria", "We were Soldiers"));
	vc.addPedidoCliente(PedidoCliente("Pedro", "Platoon"));

	string s1 = "Gladiator\nPlatoon\nWe were Soldiers\n";
	string s2 = vc.imprimirListaDeEspera();
	EXPECT_EQ(s1, s2);

	s2.erase( s2.find("Gladiator\n"), 10 );
	s2.erase( s2.find("We were Soldiers\n"), 17 );
	s2.erase( s2.find("Platoon\n"), 8 );

	EXPECT_EQ( 0, s2.size() );
	*/
}

TEST(test_1,test_f) {
	/**
	ClubeVideo vc;

	vc.addFilme( Filme("Saving Private Ryan") );
	vc.addFilme( Filme("Band of Brothers") );
	vc.addFilme( Filme("Pacific, The") );
	EXPECT_EQ(3, vc.numFilmes());

	vc.addCliente( Cliente("Mateu") );
	vc.addCliente( Cliente("Ricardo") );
	EXPECT_EQ(2, vc.numClientes());

	vc.alugar("Mateu", "Band of Brothers");
	EXPECT_EQ(2, vc.numFilmes());
	EXPECT_EQ(0, vc.numPedidos());

	vc.alugar("Ana", "Pacific, The");
	EXPECT_EQ(1, vc.numFilmes());
	EXPECT_EQ(3, vc.numClientes());
	EXPECT_EQ(0, vc.numPedidos());

	vc.alugar("Pedro", "Pacific, The");
	EXPECT_EQ(1, vc.numFilmes());
	EXPECT_EQ(4, vc.numClientes());
	EXPECT_EQ(1, vc.numPedidos());

	vc.alugar("Wagner", "Band of Brothers");
	EXPECT_EQ(1, vc.numFilmes());
	EXPECT_EQ(5, vc.numClientes());
	EXPECT_EQ(2, vc.numPedidos());

	ASSERT_THROWS(vc.alugar("Pedro", "Platoon"), FilmeInexistente);
	try {
		vc.alugar("Pedro", "Platoon");
	}
	catch(FilmeInexistente& fie) {
		string str = fie.msg();
		EXPECT_EQ("Titulo Inexistente: Platoon", str);
	}
	*/
}

TEST(test_1,test_g) {
	/**
	ClubeVideo vc;

	vc.addFilme( Filme("Saving Private Ryan") );
	vc.addFilme( Filme("Band of Brothers") );
	vc.addFilme( Filme("Pacific, The") );
	EXPECT_EQ(3, vc.numFilmes());
	EXPECT_EQ(0, vc.numClientes());
	EXPECT_EQ(0, vc.numPedidos());

	vc.alugar("Francisco", "Pacific, The");
	vc.alugar("Teresa", "Saving Private Ryan");
	vc.alugar("Bartolomeu", "Band of Brothers");
	EXPECT_EQ(0, vc.numFilmes());
	EXPECT_EQ(3, vc.numClientes());
	EXPECT_EQ(0, vc.numPedidos());

	vc.alugar("Francisco", "Band of Brothers");
	EXPECT_EQ(0, vc.numFilmes());
	EXPECT_EQ(1, vc.numPedidos());

	vc.devolver("Francisco", "Pacific, The");
	EXPECT_EQ(1, vc.numFilmes());
	EXPECT_EQ(1, vc.numPedidos());

	vc.devolver("Bartolomeu", "Band of Brothers");
	EXPECT_EQ(1, vc.numFilmes());
	EXPECT_EQ(0, vc.numPedidos());
	*/
}




