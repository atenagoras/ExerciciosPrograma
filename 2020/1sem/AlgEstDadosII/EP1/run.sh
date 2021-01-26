# Textos a serem testados
for i in criticaeconomiapoliticaIngles.txt lusiadasIngles.txt manifestocomunistaIngles.txt mariliadedirceo.txt ocapitalGrego.txt oslusiadas.txt parodiaLusiadas.txt sherlock.txt; do
    # Estruturas a serem testadas
    for j in VD VO LD LO AB TR; do
	./tso $i $j
    done
done
