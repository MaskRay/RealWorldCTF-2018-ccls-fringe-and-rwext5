;;; private/my-cc/config.el -*- lexical-binding: t; -*-
(def-package! ccls
  :defer t
  :init (add-hook! (c-mode c++-mode cuda-mode objc-mode) #'+ccls//enable)
  :config
  (setq ccls-sem-highlight-method 'font-lock)
  (add-hook 'lsp-after-open-hook #'ccls-code-lens-mode)
  (ccls-use-default-rainbow-sem-highlight)
  (evil-set-initial-state 'ccls-tree-mode 'emacs)
  (set-company-backend! '(c-mode c++-mode cuda-mode objc-mode) 'company-lsp)
  )
