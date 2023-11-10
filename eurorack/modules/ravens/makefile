all: gerbers/ravens-B_IO.zip gerbers/ravens-B_Main.zip gerbers/ravens-panel-white.zip gerbers/ravens-panel-black.zip

boards:
	mkdir -p boards

.PHONY: boards/ravens-panel-white.kicad_pcb boards/ravens-panel-black.kicad_pcb

boards/ravens-%.kicad_pcb: ravens.kicad_pcb boards
	kikit separate --source "annotation; ref: $*" "$<" "$@"

gerbers/%.zip: gerbers/%/gerbers.zip
	cp "$<" "$@"

gerbers/%/gerbers.zip: boards/%.kicad_pcb
	kikit fab jlcpcb --no-drc "$<" "gerbers/$*"
