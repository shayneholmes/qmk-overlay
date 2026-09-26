.PHONY: flash apply update clean

overlay_target := layouts/community/ergodox/shayneholmes
qmk_path := .nobackup/qmk

flash: apply
	(cd $(qmk_path) && make ergodox_ez:shayneholmes:flash)

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
