#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida
using namespace std;

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T> {

public:
    //Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    //Lembre-se de implementar o construtor e destrutor da classe
    ~MinhaListaEncadeada() override;

    std::size_t tamanho() const override;
    
    bool vazia() const override;

    size_t posicao(T dado) const override;
    
    bool contem(T dado) const override;

    void inserirNoInicio(T dado) override;
    
    void inserir(size_t posicao, T dado) override;

    void inserirNoFim(T dado) override;

    T removerDoInicio() override;

    T removerDe(size_t posicao) override;

    T removerDoFim() override;

    void remover(T dado) override;
};

template<typename T>
MinhaListaEncadeada<T>::~MinhaListaEncadeada() {
    Elemento<T> const *elemento(this->_primeiro);

    while (elemento != nullptr) {
        /* code */
        Elemento<T> *const proximo(elemento->proximo);
        delete elemento;
        elemento = proximo;
    }
}

/**
 * @brief Obtém a quantidade de itens na lista.
 * 
 * @return Um inteiro maior ou igual a 0.
 */
template<typename T>
size_t MinhaListaEncadeada<T>::tamanho() const {
    return this->_tamanho;
}


/**
 * @brief Indica se há algum item na lista ou não.
 * 
 * @return true se houver algum item na lista; false caso contrário.
 */
template<typename T>
bool MinhaListaEncadeada<T>::vazia() const {
    return (tamanho() == 0);
}


/**
 * @brief Obtém a posição de um item na lista. Lança
 * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
 * ExcecaoDadoInexistente caso o item não esteja contido na lista.
 * 
 * @param dado O item cuja posição deseja-se obter.
 * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
 * item na lista, a posição da primeira ocorrência.
 */
template <typename T>
size_t MinhaListaEncadeada<T>::posicao(T const dado) const {
    
    if(vazia()) {
        throw ExcecaoListaEncadeadaVazia{};
    }
    
    size_t i = 0;

    for(Elemento<T> const *elemento(this->_primeiro); elemento != nullptr; ++i) {
        if(elemento->dado == dado) {
            return i;
        }
        elemento = elemento->proximo;
    }

    throw ExcecaoDadoInexistente{};

}


/**
 * @brief Indica se um dado item está contido na lista ou não.
 * 
 * @param dado O item sendo buscado.
 * @return true se o item está contido na lista; false caso contrário.
 */
template<typename T>
bool MinhaListaEncadeada<T>::contem(T dado) const {
    try {
        /* code */
        return posicao(dado) < tamanho();
    }
    catch(ExcecaoDadoInexistente const&) {
        return false;
    } catch(ExcecaoListaEncadeadaVazia const&) {
        return false;
    }
    
}


/**
 * @brief Insere um item no início da lista.
 * 
 * @param dado O item sendo inserido.
 */
template<typename T>
void MinhaListaEncadeada<T>::inserirNoInicio(T dado) {
    Elemento<T> *const novo = new Elemento<T>(dado, this->_primeiro); 

    this->_primeiro = novo;
    this->_tamanho = this->_tamanho + 1;
}


/**
 * @brief Insere um item em uma posição específica da lista. Lança
 * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
 * [0, tamanho].
 * 
 * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
 * uma posição já ocupada, a posição do item que já estava naquela posição
 * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
 * fim da lista.
 * @param dado O item sendo inserido.
 */
template<typename T>
void MinhaListaEncadeada<T>::inserir(size_t posicao, T dado) {
    Elemento<T> *elemento(this->_primeiro);
    // Elemento<T> *novo = new Elemento<T>(dado, nullptr);// -> Memory Leak
    
    size_t i = 0;

    if(tamanho() < posicao || posicao < (0)) {
        throw ExcecaoPosicaoInvalida{};
    } else if(posicao == 0) {
        inserirNoInicio(dado);
    } else {
        while (i < posicao-1) {
            /* code */
            elemento = elemento->proximo;
            i++;
        }
        if(elemento != nullptr) {
            Elemento<T> *novo = new Elemento<T>(dado, nullptr); // -> Memory Leak 2
            novo->proximo = elemento->proximo;
            elemento->proximo = novo;
            this->_tamanho = this->_tamanho + 1;   
        }
    }
}


/**
 * @brief Insere um item no fim da lista.
 * 
 * @param dado O item sendo inserido.
 */
template<typename T>
void MinhaListaEncadeada<T>::inserirNoFim(T dado) {
    Elemento<T> *elemento(this->_primeiro);
    // Elemento<T> *const novo = new Elemento<T>(dado, nullptr); //-> Memory leak
    
    size_t i = 1;
    
    if(vazia()) {
        inserirNoInicio(dado);
    } else {
        while (elemento->proximo != nullptr) {
            /* code */
            elemento = elemento->proximo;
            i++;
        }
        // elemento->proximo = novo;
        // this->_tamanho = this->_tamanho + 1;
        inserir(i, dado);
    }
}


/**
 * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
 * caso não haja nenhum item na lista.
 * 
 * @return O item removido.
 */
template<typename T>
T MinhaListaEncadeada<T>::removerDoInicio() {
    Elemento<T> *elemento(this->_primeiro);

    if(vazia()) {
        throw ExcecaoListaEncadeadaVazia{};
    }
    T dado = elemento->dado;

    this->_primeiro = elemento->proximo;
    delete elemento;
    this->_tamanho = this->_tamanho - 1;

    return dado;
}


/**
 * @brief Remove um item de uma posição específica da lista. Lança
 * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
 * 
 * @param posicao Um inteiro dentro da faixa [0, tamanho).
 * @return O item removido.
 */
template<typename T>
T MinhaListaEncadeada<T>::removerDe(size_t posicao) {

    Elemento<T> *elemento(this->_primeiro);
    Elemento<T> *elementoAnterior(this->_primeiro);

    size_t i = 0;
    T dado = 0;

    if(this->_tamanho <= posicao || posicao < (0)) {
        throw ExcecaoPosicaoInvalida{};
    } else if(posicao == 0) {
        dado = removerDoInicio();
        return dado;
    } else if(posicao == this->_tamanho) {
        dado = removerDoFim();
        return dado;
    }

    while (i < posicao-1) {
        /* loop */
        elementoAnterior = elementoAnterior->proximo;
        i++;
    }

    if(elementoAnterior->proximo != nullptr) {
        elemento = elementoAnterior->proximo;
        elementoAnterior->proximo = elementoAnterior->proximo->proximo;
        dado = elemento->dado;
        delete elemento;
        this->_tamanho = this->_tamanho - 1;
    }
    return dado;
}


/**
 * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
 * caso não haja nenhum item na lista.
 * 
 * @return O item removido.
 */
template<typename T>
T MinhaListaEncadeada<T>::removerDoFim() {
    if(vazia()) {
        throw ExcecaoListaEncadeadaVazia{};
    } else if(tamanho() == 1) {
        return removerDoInicio();
    } else {
        return removerDe(tamanho()-1);
    }
}


/**
 * @brief Remove um item específico da lista. Lança
 * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
 * ExcecaoDadoInexistente caso o item não esteja contido na lista.
 * 
 * @param dado O item a ser removido. Se houver mais que um item com
 * o mesmo valor, remove a primeira ocorrência.
 */
template<typename T>
void MinhaListaEncadeada<T>::remover(T dado) {

    if(vazia()) {
        throw ExcecaoListaEncadeadaVazia{};
    } else if(contem(dado)) {
        if(posicao(dado) == 0) {
            removerDoInicio();
        } else if(posicao(dado) == this->_tamanho) {
            removerDoFim();
        } else {
            removerDe(posicao(dado));
        }
    } else {
        throw ExcecaoDadoInexistente{};
    }
}
#endif