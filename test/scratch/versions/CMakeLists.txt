define_example_program(test.scratch.versions main.cpp)

if(TARGET BDUT::BDUT)

	target_link_libraries(test.scratch.versions
		PRIVATE
			BDUT::BDUT
	)
endif()
