;;  Copyright (C) 2017, Javier Olaechea <pirata@gmail.com>

;;  This file is part of NZ.

;;  Foobar is free software: you can redistribute it and/or modify
;;  it under the terms of the GNU General Public License as published by
;;  the Free Software Foundation, either version 3 of the License, or
;;  (at your option) any later version.

;;  Foobar is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;  GNU General Public License for more details.

;;  You should have received a copy of the GNU General Public License
;;  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

(define-module (nz buffer)
  #:use-module (srfi srfi-9)
  #:use-module (ice-9 gap-buffer)
  #:export (make-buffer
            buffer-name
            buffer-insert
            buffer-contents))

(define-record-type buffer
  (%make-buffer name)
  buffer?
  (name buffer-name)
  ;; XXX: Gap buffers come with the their own point
  ;; (mark buffer-mark set-buffer-mark!)
  (contents %buffer-contents set-buffer-contents!))

(define (make-buffer name)
  (let ((buf (%make-buffer name)))
    (set-buffer-contents! buf (make-gap-buffer))
    buf))

(define (buffer-insert buf string)
  (gb-insert-string! (%buffer-contents buf) string))

(define (buffer-contents buf)
  (gb->string (%buffer-contents buf)))
