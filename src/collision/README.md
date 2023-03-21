# Satellite Collision 

## Doodles and Notes

We want to take note of the following: ABY is a framework built with a focus on the semi-honest setting, meaning that the servers are not malicious, but may be curious and try to learn more information than they should.

One way we can improve this framework is by implementing arithmetic MACs (which ironically is mentioned at the end of the paper) as a pre-computation step to verify that servers are not malicious. We can then apply the Satellite Collision problem in a setting with a malicious server and verify that security is maintained.

To prove non-maliciousness, each server generates a MAC from a given message which serves as an authentication key. The servers then exchange messages and both verify the MAC. If the MACs are both valid, execution can continue.
