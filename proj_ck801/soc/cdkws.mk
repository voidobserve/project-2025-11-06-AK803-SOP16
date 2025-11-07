.PHONY: clean All Project_Title Project_Build

All: Project_Title Project_Build

Project_Title:
	@echo "----------Building project:[ soc_test - BuildSet ]----------"

Project_Build:
	@make -r -f soc_test.mk -j 12 -C  soc_test 


clean:
	@echo "----------Cleaning project:[ soc_test - BuildSet ]----------"

