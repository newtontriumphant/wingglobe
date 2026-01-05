# WingGlobe

Quick Link Tree:

* [I. Introduction!](#i-introduction)
* [II. About This Project - Why I Chose To Make It!](#ii-about-this-project---why-i-chose-to-make-it)
* [III. About This Project - What Is It?!](#iii-about-this-project---what-is-it)
* [IV. Project Images And Technical Documentation!](#iv-project-images-and-technical-documentation)
* [V. Notes For Reviewers!](#v-notes-for-reviewers)
* [VI. Final Remarks!](#vi-final-remarks)
  
## I. Introduction!

Heyo! Thanks for reviewing my project! I'm **zsharpminor** (a.k.a. funkeudo), co-creator of FiddleStein, and this is WingGlobe, which is a (TL;DR) fully autonomous Weather-Telling Snow Globe with a custom propulsion mechanism, PWM control, backlighting, E-INK display, support for my existing ecosystem of temperature sensors, and a changeable theme. This project is being created with the support of Hack Club Blueprint, and it is an entry for Blueprint's 7-day Christmas-Themed Project Competition. I am aiming for this to be a **Tier 3** project (see section at the very end of this README for justification).

<img width="1024" height="1024" alt="image" src="https://github.com/user-attachments/assets/4a4f80e1-bac7-4fd9-a4a2-668317d73443" />

(Disclaimer: the above image is a **render**, this project is not actually built yet; CAD screenshots can be found in section IV).

**IMPORTANT REVIEWER'S NOTE:** there is a section at the **end** of this README.md file, please read through it before returning this project if possible :)

My BOM.csv is in the parent directory, additionally a link to my online BOM is https://docs.google.com/spreadsheets/d/1PTxZxDy7cq01-oPVpPEEbVuQKtVb_WSBa-1fNMrsmt8/. Thanks! :3

Before I get into why I made this project, I would like to extend a huge thanks to can can't aka kleigh (my hero), as well as sam, alex, zach, renran, deven, paolo, john cohn, olive, my teammates Max & Sidd, tanuki, nathan, everyone from AMD, and every single other equally important person that made Blueprint & Prototype happen - I literally found out about Blueprint (and Hack Club itself!) only a month and a week ago, finished a few projects and became a reviewer one week later, had the most fun I've _ever_ had at Prototype, as well as inspired myself to get back into hardware, and re-dedicate my life to electronics. I really appreciate everything each and every one of you has done, and, without further ado, here's why WingGlobe exists.

## II. About This Project - Why I Chose To Make It!

You're probably looking at this and asking me "why the hell would you make a smart snow globe?!" The answer is a bit more complex than you think!

To start off with, I'm going to say quite bluntly that this project wouldn't exist without the Blueprint Christmas Competition. Even though I've worked with hardware for years, got HM with a self playing violin, and have been a Blueprint reviewer for over a month, I **don't actually own a 3D printer** (I've been using my local library's for all of my past projects so far)! I was planning on buying one a few weeks ago, then I set myself the challenge of getting one through Blueprint by reviewing a lot and getting tickets - but my current pace is rather lackluster. In addition, I needed ideas for projects to build - Blueprint is awesome because you can ship literally anything you can imagine, as long as it's under a certain dollar amount; but I was facing a bit of a creative block until this competition came about! My first project idea was to make a laser projecting 2026 New Year's countdown - but then I remembered that New Years would be over by the time this project would be built! My goal with WingGlobe was to make a project that, while Christmas-themed, **doesn't rely on Christmas to exist** and can be used **at any time of the year**! (Christmas in July, anyone?)

Additionally, I've made an ecosystem of projects (including one that I made through Blueprint - my SmartBell!) that feature temperature and humidity sensors. I wanted them to seamlessly work together wirelessly somehow, and needed a way to make that possible. That is also the main reason I chose the ESP32-S3 for this project, besides the fact that I already owned one, that it would cut PCBA cost in half, and that it would require one less parcel to be shipped.

Finally, I've been interested in weather and meteorology in general for a few years now, and I always wanted a weather station that relied on multiple sources of data that I myself provide, in addition to the commercial weather reports available.

The Snow Globe that builds this project's core features an empty space for _any_ 3d model or figurine (assuming it's heavy enough to withstand the fan blowing snow around it!) - and I've chosen a Christmas-themed one for my first few months with WingGlobe to fit the competition's theme.

Finally, if you're wondering why it's called WingGlobe, it's a reference to aviation, where meteorology is key (bad name, I know, but it stuck!)

I wanted WingGlobe to fit these criteria:

* It **must** be overwhelmingly Christmas-themed.
* It **must** have a decent amount of hardware complexity.
* It **must** be usable outside of just Christmas season.
* It **must** predominantly integrate CAD and software instead of being _just_ hardware.
* It **must** be actually useful in everyday life.
* The PCB **must** be under 100x100mm, eligible for GSDL, and Economic PCBA.
* All parts of the project **must** be printable on the Bambu A1 Mini with minimal supports and t*nkering.

I think I did a pretty good job fitting these criteria, if I do say so myself. Anyways, enough yapping, here's what the project actually _does_:

## III. About This Project - What Is It?!

WingGlobe is basically a glorified weather report station powered by a SEEED Studios XIAO ESP-32-S3 (that I already own - more on that in Section V) that runs 16 addressable SK6812-MINI LEDs, as well as an onboard temp/humi/pressure sensor and a MOSFET powering a 4010 fan with PWM control. When the weather shifts, the snow globe is updated to match - calm weather is a white / light-blue gradient and no fan power, sunny weather is a yellow / light red gradient, sunrise and sunset are adapted to red / orange gradients, and during the night, the snow globe will be engulfed in a replica of the aurora borealis (clear sky) or simply white / dark blue (cloudy sky). The real fun begins when it rains! When the winds start, the 4010 fan's PWM controller starts to rev it up - the more dangerous the wind, the more the little snow in the globe will swirl around! I am planning to use lightweight cotton / styrofoam blend beads to imitate snow (my original idea of 3D printing them sadly failed), as well as a custom mesh that stops them from breaking the fan or going out of the top of the globe. WingGlobe's E-Ink can be customized with a touch pad on WingGlobe's PCB to show varying levels of information from varying sensors. Additionally, the fan and LEDs can be turned off with a switch on WingGlobe's side when not needed (i.e. overnight).

WingGlobe seamlessly integrates with my SmartBell, moonboard, ADS-B stations, and BarnSense projects to provide up to three different simultaneous readings of temperature, humidity, and pressure. WingGlobe also has a built-in sensor for indoor temperature and humidity (should be quite useful next to my soon-to-be 3D Printer!) For now, WingGlobe relies on commercially available data for wind readings, but I hope to create another project soon so that everything can be run off the grid and without requiring any API.

WingGlobe's ESP32-S3 connects via ESP-NOW and WiFi to fetch data from my close and far stations, respectively. You're halfway there, have a cookie! 🍪

## IV. Project Images And Technical Documentation!

### SCHEMATIC:

<img width="1118" height="780" alt="Screenshot 2026-01-01 at 3 03 01 PM" src="https://github.com/user-attachments/assets/47151f27-c2e9-4951-83d1-a10c118ad1ac" />

### PCB:

<img width="760" height="780" alt="Screenshot 2026-01-01 at 3 03 26 PM" src="https://github.com/user-attachments/assets/2e4bd1fe-ac10-4640-a26a-6008ee659375" />

<img width="687" height="670" alt="Screenshot 2026-01-01 at 3 04 12 PM" src="https://github.com/user-attachments/assets/ed6184c6-ddd9-47ab-a6f3-973570d6aa65" />

<img width="703" height="702" alt="Screenshot 2026-01-01 at 3 04 40 PM" src="https://github.com/user-attachments/assets/f8f1e349-bcc0-4118-b4ff-634d6f03f215" />

### CAD:

<img width="772" height="683" alt="Screenshot 2026-01-01 at 3 05 12 PM" src="https://github.com/user-attachments/assets/4a2877ca-7100-47ba-9e62-1342ea651cca" />

(base, with cutouts for PCB, fan, and globe)

<img width="774" height="645" alt="Screenshot 2026-01-01 at 3 05 39 PM" src="https://github.com/user-attachments/assets/460873cf-25c9-4d76-9ad5-dea4214b6cbe" />

(top, made to be glued onto base)

### CAD WITH PCB:

<img width="804" height="705" alt="Screenshot 2026-01-01 at 3 06 51 PM" src="https://github.com/user-attachments/assets/06c59372-466c-4526-b26e-339024deff24" />

(top view)

<img width="612" height="520" alt="Screenshot 2026-01-01 at 3 07 16 PM" src="https://github.com/user-attachments/assets/87db0376-c6b5-4abd-9e33-822c6f91b1fc" />

(side view)

<img width="777" height="770" alt="Screenshot 2026-01-01 at 3 07 37 PM" src="https://github.com/user-attachments/assets/b1db9c9f-5fb0-4fbf-bf11-de317cb2a600" />

(bottom view)

<img width="546" height="548" alt="Screenshot 2026-01-01 at 3 08 41 PM" src="https://github.com/user-attachments/assets/602fcd2e-8ebe-4428-ac3d-df95bd8f294b" />

(top - birds-eye view without lid)

### ASSEMBLED PRODUCT:

<img width="801" height="738" alt="Screenshot 2026-01-01 at 3 09 26 PM" src="https://github.com/user-attachments/assets/ce7afc19-97fc-4f10-add6-2b628c7f9477" />

(Front - Angle One)

<img width="841" height="704" alt="Screenshot 2026-01-01 at 3 09 43 PM" src="https://github.com/user-attachments/assets/1bc359ee-ced0-447b-9ebe-45e9ce968959" />

(Front - Angle Two)

<img width="899" height="811" alt="Screenshot 2026-01-01 at 3 10 05 PM" src="https://github.com/user-attachments/assets/2084745e-6a90-40d4-b4bc-e45073ea5036" />

(Top)

<img width="627" height="721" alt="Screenshot 2026-01-01 at 3 10 19 PM" src="https://github.com/user-attachments/assets/f23b0fa6-e25e-4c32-8243-b08b80e3b7de" />

(Side)

<img width="547" height="715" alt="Screenshot 2026-01-01 at 3 10 37 PM" src="https://github.com/user-attachments/assets/e37f2cad-4252-4724-9fdd-62d9c02be564" />

(Bottom)

### CARTS:

<img width="1920" height="1243" alt="Screenshot 2026-01-01 at 3 27 23 PM" src="https://github.com/user-attachments/assets/0d34162b-94cf-48c4-ba67-84bb96a317b3" />

(AliExpress Checkout 1)

<img width="1920" height="1243" alt="Screenshot 2026-01-01 at 3 27 32 PM" src="https://github.com/user-attachments/assets/e8a0cf12-f101-40be-9286-ebf22de88b42" />

(AliExpress Checkout 2)

<img width="1124" height="890" alt="Screenshot 2026-01-01 at 3 34 09 PM" src="https://github.com/user-attachments/assets/92e7fda4-9f2b-46c1-9be4-e8cb54cba07d" />

(JLCPCB PCB Options)

<img width="1119" height="1053" alt="Screenshot 2026-01-01 at 3 33 00 PM" src="https://github.com/user-attachments/assets/61d692b8-d362-4c04-8110-ae062c800c1f" />

(JLCPCB PCBA 1)

<img width="1133" height="965" alt="Screenshot 2026-01-01 at 3 33 20 PM" src="https://github.com/user-attachments/assets/5e0bc553-a6d5-4584-bfee-17a4511cad4e" />

(JLCPCB PCBA 2)

<img width="1128" height="960" alt="Screenshot 2026-01-01 at 3 33 39 PM" src="https://github.com/user-attachments/assets/a71da59b-926c-412f-9f8b-f2a150edc752" />

(JLCPCB PCBA 3)

<img width="1614" height="611" alt="Screenshot 2026-01-01 at 3 34 48 PM" src="https://github.com/user-attachments/assets/4021fb32-c719-483c-9fd5-146baeef1b90" />

(JLCPCB Pre-Discounts)

<img width="1920" height="1243" alt="Screenshot 2026-01-01 at 3 35 45 PM" src="https://github.com/user-attachments/assets/e2781eae-1f66-4024-be63-fd116b05f24e" />

(JLCPCB Final Checkout w/ coupon)

(**NOTE**: THIS COUPON WILL EXPIRE IN TWO DAYS, I WILL PROBABLY NOTE USE IT IN TIME. THIS IS WHY I AM REQUESTING $10 MORE THAN MY JLCPCB CART SCREENSHOT SHOWS.)

<img width="1920" height="1243" alt="Screenshot 2026-01-01 at 3 38 08 PM" src="https://github.com/user-attachments/assets/1c448f87-f1fd-40cd-aa68-0ec4bacf807d" />

(JLCPCB Final Checkout As Shown On BOM)

**NOTE**: My name was redacted using the Inspect Element tool as this repository is publically visible. If an unredacted screenshot is required, please DM me or return my project.

### I will self-fund the E-INK display due to the project tier being bumped down to T4.

### RENDER:

<img width="1024" height="1024" alt="image" src="https://github.com/user-attachments/assets/a91f5c31-5de7-4cce-ae7b-80da43aa794a" />

(My friend with Blender skills did this and it turned out amazing, so I'm making this my cover image!)

## V. Notes For Reviewers!

### Usage Of Pre-Built Devboard:

I chose to use the XIAO ESP32-S3 over making a custom ESP32 or RP2040 devboard base for three reasons:

1. I already own quite a few ESP32-S3s, making an ESP32 from scratch would more than **double** the PCBA cost at JLC, and make my order **ineligible** for GSDL shipping, which would push my budget to Tier 2.
2. I've already made a devboard, I know the hassles that are involved in wiring and routing, and I did not want to miss a single decoupling capacitor and risk my board being browned out.
3. I wanted to spend more time polishing software and CAD, and using a pre-built devboard gave me that opportunity.

Again, if this cannot be approved for Tier 3 due to a lack of complexity, I understand, and will remove parts to bring the budget down to a Tier 4.

### Why Are You Requesting Six Snow Globes?

Because it's the cheapest option available for a half-decent snowglobe on AliExpress. The next-cheapest was $7 for two, and I preferred to get six for $6.88.

All of my costs are optimized as **much as possible**, I'm using AliExpress for my items, and I've done my best to keep it in budget.

### Why Are You Requesting $10 More Than You Need For JLCPCB?

JLCPCB has a $10 coupon for PCBA (scroll up to the images section for proof). Said coupon expires in 2 days, and, knowing HCB, it will take more than 2 days to process this grant. If another coupon appears, I will return the difference immediately.

### "ThIs ReADmE iS AI gEnEraTEd!"

No, no it's not. I know how to use markdown, and I'll even occasionally use an em-dash—like so. That doesn't necessarily mean my README is automatically AI. Zero AI was used in the making of this project, and writing this text-heavy README alone took me two hours. If you need proof, I can provide a screen recording!

That's all, thanks! :D

## VI. Final Remarks!

Please ping or DM me on Slack (@zsharpminor) if you have any questions regarding my project.

Thank you so much for taking your precious time to read all the way through this extremely long README (I wanted to be well documented, okay?!)

You get a massive slice of vanilla cheesecake! :D 🍰

P.S. Happy New Year!!! I worked on this project literally as the clock struck 12 - I have a journal entry to prove it :)
