import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

X = torch.tensor([[1.0],[2.0],[3.0],[4.0]])
Y = torch.tensor([[2.0],[4.0],[6.0],[8.0]])

model = nn.Linear(1,1)

loss_fn = nn.MSELoss()
optimizer = optim.SGD(model.parameters(),lr=0.01)

losses = []

for epoch in range(1000):
    output = model(X)
    loss = loss_fn(output,Y)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    losses.append(loss.item())

print("Predicted:",model(X).detach())
print("Loss:",loss.item())

plt.plot(losses)
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Linear Regression Loss")
plt.show()
