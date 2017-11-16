hw01.out: hw01.cpp
	$(CXX) $< -pthread -o $@
clean: 
	$(RM) hw01.out
run: hw01.out
	./hw01.out > hw01.txt
	@echo done
.PHONY: clean run
