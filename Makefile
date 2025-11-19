all: approximate

approximate: Metadata.o Word.o DictionaryEntry.o Dictionary.o List.o OrderedDictionary.o approximate.o
	g++ -Wall -g -o approximate Metadata.o Word.o DictionaryEntry.o Dictionary.o List.o OrderedDictionary.o approximate.o

Metadata.o: Metadata.cc Metadata.h Word.h
	g++ -Wall -g -c Metadata.cc

Word.o: Word.cc Word.h
	g++ -Wall -g -c Word.cc

DictionaryEntry.o: DictionaryEntry.cc DictionaryEntry.h Word.h Metadata.h
	g++ -Wall -g -c DictionaryEntry.cc

Dictionary.o: Dictionary.cc Dictionary.h DictionaryEntry.h Word.h Metadata.h
	g++ -Wall -g -c Dictionary.cc

List.o: List.cc List.h Dictionary.h DictionaryEntry.h Word.h Metadata.h
	g++ -Wall -g -c List.cc

OrderedDictionary.o: OrderedDictionary.cc OrderedDictionary.h List.h Dictionary.h DictionaryEntry.h Word.h Metadata.h
	g++ -Wall -g -c OrderedDictionary.cc

approximate.o: approximate.cc Metadata.h Word.h DictionaryEntry.h Dictionary.h OrderedDictionary.h
	g++ -Wall -g -c approximate.cc

clean:
	rm -rf approximate *.o *~ pruebas/*.o pruebas/*.h pruebas/approximate pruebas/*.tmp pruebas/*.err
	for file in pruebas/*.cc; do \
		rm -rf $${file%.cc}; \
	done
