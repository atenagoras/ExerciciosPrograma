#!/bin/sh

# Parâmetros
# pqp: Nome do Programa
# K  : N° Máximo de vôos sorteados em cada intervalo de tempo
# C  : Tamanho máximo de combustível do vôo sorteado
# T  : Unidades de Tempo da Simulação
# V  : N° Máximo de horas de vôo de cada vôo sorteado para decolagem
# PrV: Probabilidade de um vôo ser sorteado
# PrE: Probabilidade de um vôo de emergência ser sorteado
# Chamada do programa com os parâmetros
# pqp aeroportos companhias K C T V PrV PrE
./pqp aeroportos companhias 100 3 1000 5 100 40
