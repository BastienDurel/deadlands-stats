all: dl

dl: c++/dl
	cp $< $@

c++/dl:
	make -C c++
