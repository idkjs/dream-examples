# project_name = dream

.PHONY: help
help:  # from https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean:  ## Clean up
	esy dune clean

.PHONY: check
check:  ## Build and check
	esy dune build @check

.PHONY: format
format:  ## Reformat with Ocamlformat
	esy dune build @fmt --auto-promote

.PHONY: server
server:  ## Run the server
	esy dune exec main
# db-up:
# 	@docker compose -f docker-compose.yml up

# db-clean:
# 	@docker container ls -qa | xargs -n1 docker container stop
# 	@docker container ls -qa | xargs -n1 docker container rm
# 	@docker volume ls -q | xargs -n1 docker volume rm

# db-down:
# 	@docker compose -f docker-compose.yml down
# 	# @docker compose -f docker-compose.yml -p $(project_name) down
