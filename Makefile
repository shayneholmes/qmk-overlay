.PHONY: apply clean flash update upload

overlay_target := layouts/community/ergodox/shayneholmes
qmk_path := qmk_firmware

flash: upload
	(cd $(qmk_path) && make ergodox_ez:shayneholmes:flash)

upload: build
	rclone copy ./qmk_firmware/.build/ergodox_ez_base_shayneholmes.hex gdrive:

build: apply
	(cd $(qmk_path) && make ergodox_ez:shayneholmes:build)

layout.json: apply
	(cd $(qmk_path) && qmk c2json -kb ergodox_ez -km shayneholmes --no-cpp) >$@

apply: $(qmk_path)/layouts
	rsync --verbose --times --mkpath --delete --recursive \
		overlay/ $(qmk_path)/$(overlay_target) -f'- .gitignore'

# The submodule path exists on a clean checkout, so use a subfolder to check
# whether we need to initialize the submodule.
$(qmk_path)/layouts:
	git submodule update --init $(qmk_path)

update: clean
	git submodule update --remote --merge

clean:
	git submodule foreach git clean -fd
