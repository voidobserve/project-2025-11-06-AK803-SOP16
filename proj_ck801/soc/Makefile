.PHONY: clean All

All:
	@echo "----------Building project:[ soc_test - BuildSet ]----------"
	@
	@cd "soc_test" && make -f "soc_test.mk" MakeIntermediateDirs && make -f "soc_test.mk" -j 16
clean:
	@echo "----------Cleaning project:[ soc_test - BuildSet ]----------"
	@cd "soc_test" && make -f  "soc_test.mk" clean
