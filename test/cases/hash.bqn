# some checks for behavior around ¯0; not strictly necessary to stay, but other tests will probably become meaningless without these!
1⊏64‿1•bit._cast ≍˘ •ParseFloat¨ "1.2"‿"-0" %% 63‿1/0‿1
! (4⥊0) (≡ ∧ ≢○(64‿1•bit._cast⊢)) 1↓¯1×π∾4⥊0
! ≢˝64‿1•bit._cast ≍˘0‿5⊏⥊(¯1⊸×≍⊢) (↕3)∾∞∾0÷0

# ¯0
! ≡´ {•Hash •ParseFloat¨ 𝕩‿"1.2"}¨ "0"‿"-0"
! 1‿0 ≡ ∊{•ParseFloat¨ 𝕩‿"1.2"}¨ "0"‿"-0"
a←(•ParseFloat¨ "1.2"‿"-0"‿"0")∾-⊸⋈0÷0 ⋄ ∊1•Hash¨ a %% 1‿1‿0‿1‿0
a←(•ParseFloat¨ "1.2"‿"-0"‿"0")∾-⊸⋈0÷0 ⋄ b←0+--a ⋄ ! a •internal.EEqual b ⋄ ! a ≡○(3⊸↑) b ⋄ ! 0≡a •Cmp b ⋄ ! a ≡○(1⊸•Hash¨) b ⋄ ! a ≡○(1⊸•Hash) b
a←(•ParseFloat¨ "1.2"‿"-0"‿"0")∾-⊸⋈0÷0 ⋄ ! (0‿3‿3‿3⊏a) ≡○•Hash (0‿4‿4‿4⊏a)

# functions
⍷⟨⊢⊢⊢, ⊢⊢⊢, +⊢⊢, ⊢+⊢, ⊢⊢+, ⊢⊢, ⊢⊢, ⊢+, 1⊸+, 1⊸+, 2⊸+, 1⟜+, 1⊸×, ⊢+⊢, ⊢⊢⊢, +⊢⊢, +˘, ×˘, +˘, +˝⟩ %% ⟨⊢⊢⊢, +⊢⊢, ⊢+⊢, ⊢⊢+, ⊢⊢, ⊢+, 1⊸+, 2⊸+, 1⟜+, 1⊸×, +˘, ×˘, +˝⟩

# various
[1‿1, 0‿1, 1‿0, 0‿0, 1‿1, 0‿0] ∊ [0‿0, 0‿1, 1‿0] %% 0‿1‿1‿1‿0‿1
[[0‿0, 0‿1, 1‿0, 1‿1], [1‿1, 0‿1, 1‿0, 0‿0]] ∊ [0‿0, 0‿1, 1‿0] %% 2‿4⥊1‿1‿1‿0‿0‿1‿1‿1
[1‿1, 0‿1, 1‿0, 0‿0, 1‿1, 0‿0] ∊○(≍⎉0) [0‿0, 0‿1, 1‿0] %% 0‿1‿1‿1‿0‿1
[[0‿0, 0‿1, 1‿0, 1‿1], [1‿1, 0‿1, 1‿0, 0‿0]] ∊○(≍⎉0) [0‿0, 0‿1, 1‿0] %% 2‿4⥊1‿1‿1‿0‿0‿1‿1‿1
⊐˜∾˜"ihxtIddKLp"‿'r'‿÷‿"EXiRowcDXx"‿'a'‿"ZNtqFbDCYZ"‿⍒‿0.05369125494326554‿↑‿5 %% ∾˜↕10
0‿1∊˜⟨"ab","cd"⟩ %% 0‿0
0‿1⊐ ⟨"ab","cd"⟩ %% 2‿2
(<"ab")∊"ab"‿"cd" %% <1
(<"cd")∊"ab"‿"cd" %% <1
(<"ef")∊"ab"‿"cd" %% <0
(127⥊"abc")⊐"abcd" %% 0‿1‿2‿127
(128⥊"abc")⊐"abcd" %% 0‿1‿2‿128
(32767⥊"abc")⊐"abcd" %% 0‿1‿2‿32767
(32768⥊"abc")⊐"abcd" %% 0‿1‿2‿32768
(127⥊"abc")⊐100⥊"ababacadabacaba" %% (100⥊0‿1‿0‿1‿0‿2‿0‿  127‿0‿1‿0‿2‿0‿1‿0)
(128⥊"abc")⊐100⥊"ababacadabacaba" %% (100⥊0‿1‿0‿1‿0‿2‿0‿  128‿0‿1‿0‿2‿0‿1‿0)
(32767⥊"abc")⊐100⥊"ababacadabacaba" %% (100⥊0‿1‿0‿1‿0‿2‿0‿32767‿0‿1‿0‿2‿0‿1‿0)
(32768⥊"abc")⊐100⥊"ababacadabacaba" %% (100⥊0‿1‿0‿1‿0‿2‿0‿32768‿0‿1‿0‿2‿0‿1‿0)
⍷ •internal.Variation⟜(↕1)¨ "Ab"‿"Ai8" %% ⟨⋈0⟩
!∘≡¨⟜⊏ 0•Hash¨ ⟨↕5 ⋄ 1↓0.5∾↕5 ⋄ 1↓'h'∾↕5⟩

{b←•internal.Unshare a←"Ai8"•internal.Variation ∾⟨16⥊0‿0‿0‿0‿0‿0‿0‿¯128, 8⥊0, 8↑2⟩ ⋄ c←8‿64•bit._cast a ⋄ ! 1‿0‿0‿1≡∊c ⋄ •internal.Keep •Hash c ⋄ ! a≡b} # make sure sign bit doesn't mutate away

# error messages
!"∊: 𝕩 cannot have rank 0" % 1‿2‿3∊0
!"⊐: 𝕨 cannot have rank 0" % 0⊐1‿2‿3
!"⊒: 𝕨 cannot have rank 0" % 0⊒1‿2‿3
!"∊: Rank of 𝕨 must be at least the cell rank of 𝕩 (⟨2⟩ ≡ ≢𝕨, 2‿2‿2 ≡ ≢𝕩)" % 1‿2∊2‿2‿2⥊1‿2
!"⊐: Rank of 𝕩 must be at least the cell rank of 𝕨 (2‿2‿2 ≡ ≢𝕨, ⟨2⟩ ≡ ≢𝕩)" % (2‿2‿2⥊1‿2)⊐1‿2
!"⊒: Rank of 𝕩 must be at least the cell rank of 𝕨 (2‿2‿2 ≡ ≢𝕨, ⟨2⟩ ≡ ≢𝕩)" % (2‿2‿2⥊1‿2)⊒1‿2
