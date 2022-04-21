# Mollab-Project
A software that computes input molecules' nomenclature.

Special thanks to: MAILLY Emeline (Physics and Chemistry teacher at Saint Paul High School in Lens, France)

The aim of the software is to compute the nomenclature of the input molecule automatically.
So far, OpenMollab doesn’t have a user-friendly User Interface to design molecules. So, another alternative method is used and is described below. The molecules currently supported by OpenMollab are the following:

Functional group |	Group
--- | ---
Alkanes	| N/A
Alkenes |	Alkenes
Alcohol |	Hydroxyl
Aldehydes |	Carbonyl
Ketones |	Carbonyl
Amines | Amines

Currently, each molecule can belong to only one functional group.
In order to get the nomenclature of your molecule, you must follow those steps:

–	Draw your molecule on a piece of paper or visualize it
–	Count the amount N of atoms and the amount B of bounds (including double bounds)
–	On the first line of the command, type N and B separated by a space. For instance, for the butane, N = 14 and B = 13 as its brut formula is C4H10, the first line should be: 

14 13
